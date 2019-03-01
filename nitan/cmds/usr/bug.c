// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

#define DATA_PATH      "/data/bug/"
#define BUG_D   "/adm/daemons/bugd"
#define PER_REPORT_TIME_LIMIT   60

#define LIST_OPT_ALL    (1<<0)

string help = @HELP

bug -a                          新增 bug 回報
bug -l                          列出 bug 資料
bug <編號>                      讀取 bug 詳細內容
bug -r <編號>                   回應 bug 處理情形       巫師專用
bug -d <編號>[.<回復編號>]      刪除 bug 某篇或某篇回復 巫師專用
bug                             讀取錯誤回溯            巫師專用
bug [ID]                        讀取某人的錯誤回溯      巫師專用

HELP;

string big_number_check(mixed bn)
{
        int negtive;

        if( !bn ) return 0;

        if( intp(bn) )
                return bn+"";
        else if( !stringp(bn) )
                return 0;

        if( bn[0] == '-' )
        {
                bn = bn[1..];
                negtive = 1;
        }

        bn = replace_string(bn, ",", "");

/*
        if( bn[<1] == 'k' || bn[<1] == 'K' )
                bn = bn[0..<2]+"000";
        else if( bn[<1] == 'm' || bn[<1] == 'M' )
                bn = bn[0..<2]+"000000";
        else if( bn[<1] == 'g' || bn[<1] == 'G' )
                bn = bn[0..<2]+"000000000";
*/
        while(bn[0]=='0') bn = bn[1..];

        foreach(int i in bn)
                if( i < '0' || i > '9' )
                        return 0;

        if( bn == "" )
                return 0;
        else
                return negtive ? "-"+bn : bn;
}

void edit_bug_content(object me, string title, string content)
{
        string number;

        if( time()-query_temp("bug_report", me)<PER_REPORT_TIME_LIMIT )
                return tell_object(me, "你必須再隔 "+(PER_REPORT_TIME_LIMIT + query_temp("bug_report", me) - time())+" 秒後才能再回報一次 Bug。\n"NOR);

        number = BUG_D->add_bug(me, title, content);

        tell_object(me, HIY"感謝你的 Bug 回報使得這個世界更加完美。\n"NOR);
        tell_object(me, HIY"\n已將你所回報的 Bug 存入資料庫中，編號為 "+number+"，請利用 bug -l 隨時注意處理狀況。\n"NOR);

        set_temp("bug_report", time(), me);

        me->finish_input();
}

void input_bug_title(object me, string title)
{
        if( !title || !title[0] )
        {
                tell_object(me, "取消 Bug 回報輸入。\n");
                return me->finish_input();
        }

        if( strlen(filter_color(title,1)) > 30 )
        {
                tell_object(me, "回報主題不得超過 30 個字元。\n");
                return me->finish_input();
        }

        if( query_temp("big5", me) )
                title = LANGUAGE_D->Big52GB(title);

        tell_object(me, "你所輸入的 Bug 回報主題為：“"+title+NOR+"”\n");
        tell_object(me, HIY"請輸入欲回報的 Bug 詳細內容。\n"NOR);
        me->edit( (: edit_bug_content, me, title :) );
}

void edit_reply_content(object me, string number, string status, string content)
{
        BUG_D->reply_bug(me, number, status, content);

        tell_object(me, "回應編號第 "+number+" 號 Bug 完畢。\n");

        me->finish_input();
}

void confirm_input_reply(object me, string number, string status, string confirm)
{
        if( stringp(confirm) )
                confirm = lower_case(confirm);

        switch(confirm)
        {
                case "yes":
                case "y":
                        tell_object(me, HIY"請輸入處理詳細內容。\n"NOR);
                        me->edit( (: edit_reply_content, me, number, status :) );
                        return;
                default:
                        tell_object(me, HIY"不輸入處理詳細內容。\n"NOR);
                        BUG_D->reply_bug(me, number, status);
                        me->finish_input();
                        break;
        }
}


void input_reply_status(object me, string number, string arg)
{
        string status;

        switch(arg)
        {
                case "1":       status = HIR"未處理"NOR;        break;
                case "2":       status = HIY"處理中"NOR;        break;
                case "3":       status = HIC"已修復"NOR;        break;
                case "4":       status = HIR"無法修復"NOR;      break;
                case "5":       status = HIW"不需處理"NOR;      break;
                case "6":       status = HIM"需再回報"NOR;      break;
                default:        status = HIR"未處理"NOR;        break;
        }

        tell_object(me, "是否輸入處理詳細內容？(Yes/No):");
        input_to( (: confirm_input_reply, me, number, status :) );
}

int main(object me, string arg)
{
        object ob;
        string number;
        mapping data;

        MYGIFT_D->check_mygift(me, "newbie_mygift/bug");
        if( wizardp(me) )
        {
                if( !arg || !arg[0] )
                {
                        if( !query_temp("bug_msg", me) )
                                return notify_fail("你身上沒有錯誤回溯資料。\n");

                        me->start_more(query_temp("bug_msg", me));
                        return 1;
                }
                else if( ob = find_player(arg) )
                {
                        if( !query_temp("bug_msg", ob) )
                                return notify_fail(ob->query_idname()+"身上沒有錯誤回溯資料。\n");
                        me->start_more(query_temp("bug_msg", ob));
                        return 1;
                }
                else if( sscanf(arg, "-r %s", number) )
                {
                        if( !BUG_D->bug_exists(number) )
                                return notify_fail("並沒有編號 "+number+" 的 Bug 存在。\n"NOR);

                        data = restore_variable(read_file(DATA_PATH+number)); 
                        tell_object(me, HIY"請輸入目前處理狀況編號：\n[1]"HIR"未處理"NOR" [2]"HIY"處理中"NOR" [3]"HIC"已修復"NOR" [4]"HIR"無法修復"NOR" [5]"HIW"不需處理"NOR" [6]"HIM"需再回報"NOR"\n");
                        tell_object(me, CYN+"\n"+data["content"]+"\n"+NOR+":"); 
                        input_to( (: input_reply_status, me, number :) );
                        return 1;
                }
                else if( sscanf(arg, "-d %s", number) )
                {
                        int reply;

                        sscanf(number, "%s.%d", number, reply);

                        if( !BUG_D->bug_exists(number) )
                                return notify_fail("並沒有編號 "+number+" 的 Bug 存在。\n"NOR);

                        if( reply > 0 )
                        {
                                BUG_D->remove_bug(me, number, reply);
                                tell_object(me, "刪除編號第 "+number+" 號 Bug 的第 "+reply+" 篇回應。\n"NOR);
                        }
                        else
                        {
                                BUG_D->remove_bug(me, number);
                                tell_object(me, "刪除編號第 "+number+" 號 Bug 的所有資料。\n"NOR);
                        }

                        return 1;
                }
        }

        if( !arg )
                return notify_fail(help);

        else if( arg == "-l" )
        {
                me->start_more(BUG_D->list_bug(1));
                return 1;
        }
        else if( arg == "-a" )
        {
                tell_object(me, HIW"歡迎使用"WHT"臭蟲(Bug)回報系統\n"NOR HIG"回報 Bug 時請詳述發生時間、所在的位置、下達過的指令與系統顯示的訊息\n詳細的資料將可以幫助巫師快速解決你遇到的 Bug。\n"NOR);
                tell_object(me, HIY"請輸入欲回報的 Bug 主題(僅主題，非詳細內容)，或直接按 Enter 取消輸入。\n:"NOR);
                input_to( (: input_bug_title, me :) );
                return 1;
        }
        else if( big_number_check(arg) )
        {
                if( !BUG_D->bug_exists(arg) )
                        return notify_fail("並沒有編號 "+arg+" 的 Bug 存在。\n"NOR);

                tell_object(me, BUG_D->query_bug(arg));
                return 1;
        }
        else return notify_fail(help);
}

int help(object me)
{
        write(help);
        MYGIFT_D->check_mygift(me, "newbie_mygift/bug");
        return 1;
}
