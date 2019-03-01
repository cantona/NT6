// This program is a part of NT MudLIB

#include <ansi.h>
#include <mudlib.h>

#define DATA_PATH               "/data/bug/"
#define DEFAULT_LOAD            10
#define SERIAL_NUMBER_KEY       "bug"

#define REPLY_AUTHOR            0
#define REPLY_MESSAGE           1

#define LIST_OPT_ALL    (1<<0)

string *buginfo;

int bug_exists(string number)
{
        return file_exists(DATA_PATH+number);
}

void reset_buginfo()
{
        buginfo = allocate(0);

        foreach(string file in sort_array(get_dir(DATA_PATH), (: (to_int($1) < to_int($2)) ? 1 : -1 :))[0..DEFAULT_LOAD-1])
                buginfo += ({ restore_variable(read_file(DATA_PATH+file)) });
}

// 蹈堤 Bug 蹈桶
string list_bug(int options)
{
        int len;
        string listmsg;
        string *list_buginfo;

        if( options & LIST_OPT_ALL )
        {
                list_buginfo = allocate(0);

                foreach(string file in get_dir(DATA_PATH))
                        list_buginfo += ({ restore_variable(read_file(DATA_PATH+file)) });
        }
        else
                list_buginfo = buginfo;

        list_buginfo = sort_array(list_buginfo, (: (to_int($1["number"]) < to_int($2["number"])) ? 1 : -1 :));
        listmsg =  "\n"+MUD_FULL_NAME+HIY" 堪單隙惆炵苀\n"NOR;
        listmsg += WHT"岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n"NOR;
        listmsg += "晤瘍 隙惆氪                   翋枙                          揭燴袨怓  隙茼\n";
        listmsg += WHT"岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n"NOR;

        foreach( mapping data in list_buginfo )
        {
#ifdef LONELY_IMPROVED
                len = 0;
#else
                len = color_len(data["status"]);
#endif
                listmsg += sprintf(HIY"%-4s"NOR" %-24s %-:30s%-"+(8+len)+"s %5s\n", data["number"],
                                   data["author_idname"], data["title"], data["status"],
                                   sizeof(data["reply"]) ? sizeof(data["reply"])+"" : "");
        }
        listmsg += WHT"岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n"NOR;

        if( options & LIST_OPT_ALL )
                listmsg += "蹈堤垀衄隙惆訧蹋\n";
        else
                listmsg += "蹈堤郔輪 "+DEFAULT_LOAD+" 砐隙惆訧蹋\n";

        return listmsg;
}

// 陔崝 Bug 訧蹋
string add_bug(object me, string title, string content)
{
        mapping bugdata = allocate_mapping(0);

        if( !objectp(me) || !stringp(title) || !stringp(content) )
                error("BUG_D add_bug() 渣昫怀統杅");

        bugdata["time"] = time();
        bugdata["where"] = base_name(environment(me));
        bugdata["number"] = SERIAL_NUMBER_D->query_serial_number(SERIAL_NUMBER_KEY);

        bugdata["author_id"] = me->query_id(1);
        bugdata["author_idname"] = me->query_idname();

        bugdata["title"] = title;
        bugdata["content"] = content;

        bugdata["status"] = HIR"帤揭燴"NOR;

        bugdata["reply"] = allocate(0);

        assure_file(DATA_PATH+bugdata["number"]);
        if( write_file(DATA_PATH+bugdata["number"], save_variable(bugdata)) )
                reset_buginfo();
        else
                error("BUG_D 拸楊揣湔陔崝 bug 訧蹋");

        CHANNEL_D->channel_broadcast("sys", HIW+me->query_idname()+HIW"陔崝 Bug 隙惆ㄛ※"+title+NOR+HIW"§ㄛ晤瘍ㄩ"+bugdata["number"]+"﹝");

        return bugdata["number"];
}

// 隙茼 Bug 揭燴倛
varargs void reply_bug(object me, string number, string status, string message)
{
        mapping data;

        if( !bug_exists(number) )
                error("BUG_D reply_bug() 拸森紫偶");
        else
                data = restore_variable(read_file(DATA_PATH+number));

        data["status"] = status;
        CHANNEL_D->channel_broadcast("sys", me->query_idname()+"党蜊晤瘍菴 "+number+" 瘍 Bug 揭燴袨錶峈※"+status+"§");

        if( find_player(data["author_id"]) )
                tell_object(find_player(data["author_id"]), me->query_idname()+"隙茼晤瘍菴 "+number+" 瘍 Bug 揭燴袨錶峈※"+status+"§﹝\n");

        if( !undefinedp(message) )
        {
                if( !arrayp(data["reply"]) )
                        data["reply"] = allocate(0);

                data["reply"] += ({ ({ me->query_idname(), message }) });
                CHANNEL_D->channel_broadcast("sys", me->query_idname()+"怀晤瘍菴 "+number+" 瘍 Bug 揭燴隙茼");
        }

        write_file(DATA_PATH+number, save_variable(data), 1);
        reset_buginfo();
}

// 痄壺 Bug 訧蹋
varargs void remove_bug(object me, string number, int reply)
{
        if( !bug_exists(number) )
                error("BUG_D remove_bug() 拸森紫偶");

        // 刉壺淕跺 Bug 訧捅
        if( undefinedp(reply) )
        {
                if( !rm(DATA_PATH+number) )
                        error("BUG_D remove_bug() 拸楊刉壺紫偶");

                reset_buginfo();
        }
        // 刉壺笢珨跺隙茼訧蹋
        else
        {
                mapping data = restore_variable(read_file(DATA_PATH+number));

                reply--;

                if( reply < sizeof(data["reply"]) && reply >= 0 )
                {
                        if( reply == 0 )
                                data["reply"] = data["reply"][1..];
                        else
                                data["reply"] = data["reply"][0..reply-1] + data["reply"][reply+1..];
                }

                write_file(DATA_PATH+number, save_variable(data), 1);
                reset_buginfo();
        }
}

// 脤戙 Bug 訧蹋
string query_bug(string number)
{
        string bugmsg;
        mapping data;
        int len;

        if( !bug_exists(number) )
                error("BUG_D query_bug() 拸森紫偶");
        else
                data = restore_variable(read_file(DATA_PATH+number));

#ifdef LONELY_IMPROVED
                len = 0;
#else
                len = color_len(data["status"]);
#endif

        bugmsg =  sprintf(HIM"晤瘍"NOR" %-20s "HIM"翋枙"NOR" %s\n"NOR, data["number"], data["title"]);
        bugmsg += sprintf(HIM"奀潔"NOR" %-20s "HIM"隙惆"NOR" %s\n", TIME_D->replace_ctime(data["time"]), data["author_idname"]);
        bugmsg += sprintf(HIM"袨錶"NOR" %-"+(20+len)+"s "HIM"隙茼"NOR" %d\n", data["status"], sizeof(data["reply"]));
        bugmsg += sprintf(HIM"華萸"NOR" %s\n", data["where"]);
        bugmsg += WHT"岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n"NOR;
        bugmsg += data["content"]+"\n";

        if( sizeof(data["reply"]) )
        {
                int replies;

                foreach( string *reply in data["reply"] )
                {
                        replies++;
                        bugmsg += HIY"\n\n*** 菴 "+replies+" 隙茼ㄩ"+reply[REPLY_AUTHOR]+HIY+" ***\n"NOR;
                        bugmsg += reply[REPLY_MESSAGE]+NOR"\n";
                }
        }

        bugmsg += WHT"岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸岸\n"NOR;

        return bugmsg;
}

void create()
{
        reset_buginfo();
}
string query_name()
{
        return "堪單隙惆炵苀(BUG_D)";
}
