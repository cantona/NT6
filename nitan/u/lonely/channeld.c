// This program is a part of NT MudLIB

#define PLAYER               0
#define TEACHER              1
#define IMMORTAL             2
#define WIZARD               4

#define CHAT                 (1<<0)        //閒聊
#define RUMOR                (1<<1)        //謠言
#define MESS                 (1<<2)        //江湖
#define WIZ                  (1<<3)        //巫師
#define SYS                  (1<<4)        //系統
#define NCH                  (1<<5)        //監測
#define NEWS                 (1<<6)        //新聞
#define SOS                  (1<<7)        //求助
#define GWIZ                 (1<<8)        //國際巫師
#define OTHER                (1<<9)        //其他
#define AD                   (1<<10)       //廣告
#define FAMILY               (1<<11)       //門派
#define WAR                  (1<<12)       //戰場
#define TCH                  (1<<13)       //報告 
#define PARTY                (1<<14)       //幫派
#define STOCK                (1<<15)       //股票
#define AUC                  (1<<16)       //拍賣
#define DEBUG                (1<<17)       //測試
#define COMBAT		     (1<<18)	   //戰鬥
#define GROUP		     (1<<19)       //隊伍
#define SPORT		     (1<<20)	   //運動

#define SPECIAL_NPC     ({ "/adm/npc/youxun" })

#include <ansi.h>
#include <mudlib.h>
#include <net/dns.h>
#include <net/macros.h>
#include <localtime.h>

inherit F_DBASE;

#define DEFAULT_REFUSE  ( NCH | OTHER | AD )

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}

mapping channels;
mapping users;
nosave int water_number;
mapping query_chann() { return channels; }

nosave string msg_log;
nosave int log_from;

string *info =
({
    ({
        TCH,
        "tch",
        TEACHER,
        HIY "【"NOR HBRED HIW"導師"NOR HIY"】"NOR,
        ([
                "msgcolor"      : NOR HBRED HIW
        ]),
    }),
    ({
        WAR,
        "war",
        PLAYER,
        BLU "【"HIB"戰場"NOR BLU"】"NOR,
        ([
                "msgcolor"      : NOR HIR,
                "noemote"       : 1,
        ]),
    }),
    ({
        CHAT,
        "chat",
        PLAYER,
        CYN "【"HIC"閒聊"NOR CYN"】"NOR,
        ([
                "msgcolor"      : NOR HIC,
        ]),
    }),
    ({
        RUMOR,
        "rumor",
        PLAYER,
        MAG "【"NOR HIM"謠"NOR MAG"言"NOR HIM"】"NOR,
        ([
                "wizlevel"      : 1,
                "msgcolor"      : NOR HIM,
        ])
    }),
    ({
        MESS,
        "mess",
        PLAYER,
        HIG "【"HIR"江湖"NOR HIG"】"NOR,
        ([
                "time"          : 1,
                "msgcolor"      : NOR HIG,
                "notalk"        : 1,
        ])
    }),
    ({
        WIZ,
        "wiz",
        IMMORTAL,
        YEL "【"HIY"巫師"NOR YEL"】"NOR,
        ([
                "msgcolor"      : NOR HIG,
                "nameraw"       : 1,
        ]),
    }),
    ({
        SYS,
        "sys",
        WIZARD,
        RED "【"RED"系"NOR RED"統"NOR RED"】"NOR,
        ([
                "time"          : 1,    // 顯示時間
                "msgcolor"      : NOR RED,
        ]),
    }),
    ({
        NCH,
        "nch",
        WIZARD,
        BLU "【"NOR HIB"監測"NOR BLU"】"NOR,
        ([
                "time"          : 1,
                "msgcolor"      : NOR HIB,
                //"listener"    : ({ get_object(INTERMUD2_D) });
        ]),
    }),
    ({
        DEBUG,
        "debug",
        WIZARD,
        WHT "【"NOR HIW"調試"NOR WHT"】"NOR,
        ([
                "time"          : 1,
                "msgcolor"      : NOR HIW,
        ]),
    }),    
    ({
        NEWS,
        "news",
        PLAYER,
        GRN "【"HIG"新"NOR GRN"聞"HIG"】"NOR,
        ([
                "time"          : 1,
                "nameraw"       : 1,
                "msgcolor"      : NOR YEL,
                "notalk"        : 1,
        ]),
    }),
    ({
        //GWIZ 被別的地方定義過
        256,
        "gwiz",
        WIZARD,
        GRN "【"HIG"網際%T"NOR GRN"】"NOR,
        ([
                "nameraw"       : 1,
                "msgcolor"      : NOR HIG,
                "intermud"      : INTERMUD2_D,
                "channel"       : "CREATOR",
                "subchannel"    : 1,
                "newtitle"      : (: stringp($1) ? "-"+$1 : "" :),
        ]),
    }),
    ({
        OTHER,
        "other",
        PLAYER,
        CYN "【"NOR CYN"未知%T"NOR CYN"】"NOR,
        ([
                "msgcolor"      : NOR CYN,
                "intermud"      : INTERMUD2_D,
                "channel"       : "",
                "subchannel"    : 1,
                "newtitle"      : (: stringp($1) ? ("-"+HIG+$1+NOR) : "" :),
        ]),
    }),
    ({
        AD,
        "ad",
        PLAYER,
        WHT "【"NOR HIK"廣告" NOR WHT"】"NOR,
        ([
                "nameraw"       : 1,
                "noemote"       : 1,
                "msgcolor"      : NOR HIK,
        ]),
    }),
    ({
        FAMILY,
        "family",
        PLAYER,
        HIW"【"NOR"%T"NOR HIW"】"NOR,
        ([
                "msgcolor"      : NOR HIG,
                "subchannel"    : 1,
                "filter"        : (: $1->query_family() == (stringp($2) ? $2 : $2->query_family()) || wiz_level($1) > 1 :),
                "newtitle"      : (: (stringp($1) ? $1 : $1->query_family()) || "無門派":),
        ]),
    }),
    ({
        PARTY,
        "party",
        PLAYER,
        HIW"【"NOR"%T"NOR HIW"】"NOR,
        ([
                "msgcolor"      : NOR HIG,
                "subchannel"    : 1,
                "filter"        : (: $1->query_bunch() == (stringp($2) ? $2 : $2->query_bunch()) || wiz_level($1) > 1 :),
                "newtitle"      : (: (stringp($1) ? $1 : $1->query_bunch()) || "無幫派":),
        ]),
    }),
    ({
        STOCK,
        "stock",
        PLAYER,
        YEL "【"NOR HIY"股"NOR YEL"市" NOR HIY"】"NOR,
        ([
                "time"          : 1,
                "nameraw"       : 1,
                "msgcolor"      : NOR HIR,
        ]),
    }),
    ({
        AUC,
        "auc",
        PLAYER,
        BLU "【"NOR HIB"拍賣" NOR BLU"】"NOR,
        ([
                "time"          : 1,
                "notalk"        : 1,
                "msgcolor"      : NOR HIY,
        ]),
    }),
    ({
    	COMBAT,
	"combat",
	PLAYER,
        HIR "【"NOR RED"戰"HIR"鬥" NOR HIR"】"NOR,
	([
	        "time"	        : 1,
	        "notalk"	: 1,
                "msgcolor"      : NOR HIR,
	]),
    }),
    ({
	SOS,
	"sos",
	PLAYER,
        HIG "【"NOR HIR"求助" NOR HIG"】"NOR,
	([
	        "msgcolor"      : NOR HIR,
	        "nameraw"       : 1,
	]),
    }),
    ({ 
	GROUP,
	"gt",
	PLAYER,
	HIW"【"NOR WHT"%T"HIW"】"NOR,
	([
	        "msgcolor"      : NOR HIW,
	        "subchannel":	1,
                "filter"        : (: query_temp("battle/team_name", $1) == (stringp($2) ? $2 : query_temp("battle/team_name", $2)) || wiz_level($1) > 1 :),
                "newtitle"      : (: (stringp($1) ? $1 : query_temp("battle/team_name", $1)) || "無隊伍":),
	]),
    }),
     ({ 
        SPORT,
	"sport",
	PLAYER,
	WHT "【"NOR HIW"運"NOR WHT"動" NOR HIW"】"NOR,
	([
	        "msgcolor"      : NOR HIW,
	        "time"	:	1,
	        "notalk"	:	0,
	]),
    }),
});

nosave mapping replace_word = ([
        "幹你娘":       "******",
        "媽逼":         "******",
        "媽的逼":       "******", 
        "媽個逼":       "******",
        "媽的個逼":     "******",   
        "逼養的":       "******",
        "傻逼":         "******",
]);

int valid_channel(int level, string channel)
{
        foreach(string *data in info)
        {
                if( data[1] == channel && level >= atoi(data[2]) )
                        return 1;
        }

        return 0;
}

varargs int do_channel(object me, string channel, string msg, mixed raw)
{
        int t,emote,internal_flag,name_raw;
        object *fit_users;
        class channel_class ch;
        string channel_title, idname, send_msg, time, my_id, my_idname, color, subchannel;
        string lfn;
        mixed lt; 

        if( !channel || channel == "" || !me ) return 0;

        if( query("chblk_on", me) )
                return notify_fail("你的聊天頻道給關閉了！唯一的辦法就是請求在線玩家投票開通。\n");
                                        
        if( me->is_chatter() )
                return notify_fail("聊天魂魄目前不能使用各種頻道。\n");
        
        if( playerp(me) && me->ban_say(1) ) return 0;
        
        // 檢查是否為表情指令
        if( channel[<1] == '*' ) { emote = 1; channel = channel[0..<2]; }

        if( sscanf(channel, "gwiz-%s", subchannel) ) channel = "gwiz"; 

        if( !classp(ch = channels[channel]) ) return 0;

        // player broadcasting need consume jing
        if( playerp(me) && !wizardp(me) && channel == "rumor" &&
            !objectp(present("rumor generator", me)) )
                if( query("jing", me)>50 ) 
                        addn("jing",-random(36), me); 
                else
                        return notify_fail("你已經沒力氣散播謠言了！\n");
        
        if( query("doing", me) == "scheme"){
                if( query("jing", me)<100 )
                        return notify_fail("你現在的精神不濟，等一會兒吧。\n");
                addn("jing", -50, me);
        }
                
        if( channel == "family" && interactive(me) && !wizardp(me) && !query("family", me) )
                return notify_fail(pnoun(2, me)+"並未加入任何門派。\n");
                
        if( channel == "party" && interactive(me) && !wizardp(me) && !query("party", me) )
                return notify_fail(pnoun(2, me)+"並未加入任何幫派。\n");

        
        my_id = me->query_id(1); // 不帶顏色
        name_raw = ch->extra["nameraw"];
        my_idname = me->query_idname(name_raw); // 是否假裝了別人

        // 若有子頻道標記, 則分析子頻道名稱
        if( ch->extra["subchannel"] )
                if( msg && sscanf(msg, "[%s] %s", subchannel, msg) ) internal_flag=1;
        // 檢查本頻道之特殊替換頻道名
        if( ch->extra["newtitle"] )
        {

                channel_title = replace_string(ch->msg, "%T", evaluate(ch->extra["newtitle"], stringp(raw) ? raw : (wizardp(me)||previous_object(1)==find_object(INTERMUD2_D)) ? subchannel || me : me));
        }
        else
                channel_title = ch->msg;

        // 假如是使用者, 則檢查頻道注冊
        if( interactive(me) && !(ch->number & users[me]) )
        {
                if( wiz_level(my_id) < ch->level ) return 0;

                users[me] |= ch->number;
                set("channels", query("channels",me) | ch->number, me);
                tell(me, "開啟 "+channel_title+" 頻道。\n");

                if( !msg ) return 1;
        }

        // 若沒有輸入訊息
        msg = msg || (emote ? "看起來表情豐富。" : "..." );

        // 檢查ID, NAME
        idname = my_idname || query("channel_id", me) || "NO_IDNAME";
        if( channel == "rumor" && idname == "NO_IDNAME" ) idname = "";

        // 整理出正在使用本頻道的頻道使用者
        // bug
        fit_users = keys(users);
        for( int i=0;i<sizeof(fit_users);i++ )
{
                if( !intp(users[fit_users[i]]) )
{
delete("channels", fit_users[i]);
                        map_delete(users, fit_users[i]);
}
}
                        
        fit_users = keys(filter(users, (: $(ch->number) & $2 :)));
        fit_users -= ({ 0 }); 

        // 檢查本頻道的使用之過濾條件
        if( ch->extra["filter"] )
        {
                if( sizeof(fit_users) )
                        fit_users = filter(fit_users, ch->extra["filter"], stringp(raw) ? raw : (wiz_level(me) > 1 ? subchannel || me : me));
        }


        // 若此頻道有顯示時間標記
        if( ch->extra["time"] == 1 )
                time = HIW+ctime(time())[11..15]+NOR" ";
        else if( ch->extra["time"] == 2 )
                time = HIW+ctime(TIME_D->query_game_time())[11..15]+NOR" ";
        else
                time = "";

        // 若使用表情模式
        if( emote )
        {
                string verb, arg;
                if( ch->extra["noemote"] )
                        return notify_fail("這個頻道不支持表情動詞。\n");
                verb = msg;
                sscanf(msg, "%s %s", verb, arg);

                if( EMOTE_D->is_emote(verb) )
                        msg = EMOTE_D->do_emote(me, verb, arg, 1) || (idname + msg);
                else
                        msg = idname + msg;
        }

        // 若此頻道有設定特定訊息顏色
        if( ch->extra["msgcolor"] )
        {
                color = ch->extra["msgcolor"];
/*
                msg = remove_ansi(msg);
                idname = remove_ansi(idname);
*/
        }
        else
                color = "";

        // 限制洗熒幕的行為
        if( undefinedp(raw) && previous_object() != this_object() && me->is_character() )
        {
                int nowtime = time();

                if( nowtime - query_temp("lastchat/time", me) < 1 )
                {
                        if( addn_temp("lastchat/warning", 1, me) > 100 )
                        {
                                tell(me, "由于"+pnoun(2, me)+"大量重覆嘗試不合法的頻道發言動作，從現在起將自動封鎖"+pnoun(2, me)+"的指令功能。\n");
                                set("cmdlimit", 30, me);
                                CHANNEL_D->channel_broadcast("sys", me->query_idname()+"大量重覆嘗試不合法的頻道發言動作，從現在起將自動限制指令速度。\n");
                        }
                        return notify_fail("公開頻道不能連續發送訊息。\n");
                }
                if( query_temp("lastchat/msg", me) == msg && nowtime - query_temp("lastchat/time", me) < 300 )
                {
                        if( addn_temp("lastchat/repeattimes", 1, me) > 5 )
                        {
                                if( addn_temp("lastchat/warning", 1, me) > 100 )
                                {
                                        tell(me, "由于"+pnoun(2, me)+"大量重覆嘗試不合法的頻道發言動作，從現在起將自動封鎖"+pnoun(2, me)+"的指令功能。\n");
                                        set("cmdlimit", 30, me);
                                        CHANNEL_D->channel_broadcast("sys", me->query_idname()+"大量重覆嘗試不合法的頻道發言動作，從現在起將自動限制指令速度。\n");
                                }
                                return notify_fail("公開頻道不能連續發送相同訊息。\n");
                        }
                }
                else
                {
                        set_temp("lastchat/msg", msg, me);
                        delete_temp("lastchat/repeattimes", me);
                }

                set_temp("lastchat/time", nowtime, me);
        }
        // 玩家無法用 News 頻道發言
        if( ch->extra["notalk"] )
        {
                if( !wizardp(me) && interactive(me) )
                {
                        return notify_fail("玩家無法使用這個頻道發言。\n");
                }
        }
        // 若是網際頻道
        if( ch->extra["intermud"] && interactive(me) )
        {
                string intermud_msg = msg;
                if( emote ) intermud_msg = replace_string(msg, my_idname, my_idname[0..<2] + "@NT)");

                if( channel == "gwiz" )
                        ch->extra["intermud"]->send_gwiz_msg(subchannel, capitalize(me->query_id(1)), me->query_name(), intermud_msg, emote);
                else
                if((!internal_flag && subchannel!="") || ( internal_flag && member_array(subchannel,keys(channels))==-1 )) 
                        ch->extra["intermud"]->send_gchannel_msg(subchannel, capitalize(me->query_id(1)), me->query_name(), intermud_msg, emote);
                else         subchannel="站內";
        }

        // 若有純訊息參數或表情參數, send_msg = 頻道名稱 + 訊息
        if( !undefinedp(raw) || emote )
                send_msg = channel_title+time+color;
        else
                send_msg = channel_title+time+color+idname+"："+color;


        // 處理精簡字串
        send_msg = send_msg + msg + NOR + (noansi_strlen(msg) > 0 && remove_ansi(msg)[<1] == '\n' ? "" : "\n");


        // replace string
        foreach(string a , string b in replace_word)
        send_msg=replace_string(send_msg,a,b);
        
        // replace ansi for %^RED%^
	//send_msg = replace_usa_ansi(send_msg);

        fit_users -= ({ 0 });
        // 使用者權限處理, 等級高等于說話者直接顯示名稱
        if( ch->extra["wizlevel"] && me->is_character() )
        {
                int my_level = wiz_level(my_id);
                string level_send_msg;
                object *level_fit_users;

                level_fit_users = filter(fit_users, (: wizardp($1) && $(my_level) <= wiz_level($1) :));
                if( random(50) || wizardp(me) || !userp(me) )
                        switch(query("env/rumor", me))
                {
                case 1:
                        {
                                string random_idname;
                                object* fit_users_without_wiz = filter_array(fit_users, (: !wizardp($1) :));

                                if( !sizeof(fit_users_without_wiz) )
                                        random_idname = fit_users[random(sizeof(fit_users))]->query_idname();
                                else
                                        random_idname = fit_users_without_wiz[random(sizeof(fit_users_without_wiz))]->query_idname();

                                level_send_msg = replace_string(send_msg, my_idname, "["+my_idname+"]-假冒的" + random_idname );
                                send_msg = replace_string(send_msg, my_idname, "假冒的" + random_idname );
                                break;
                        }
                case 2:
                        {
                                if( undefinedp(query_temp("rumor_serial",me)) )
                                {
                                        water_number += 1 + random(50);
                                        set_temp("rumor_serial", water_number,me);
                                }
                                level_send_msg = replace_string(send_msg, my_idname, "["+my_idname+"]-"+(query("gender", me) == "男性"?"Mr.":"Miss")+  query_temp("rumor_serial",me) );
                                send_msg = replace_string(send_msg, my_idname, (query("gender", me) == "男性"?"Mr.":"Miss")+  query_temp("rumor_serial",me));

                                break;
                        }
                default:
                        level_send_msg = replace_string(send_msg, my_idname, "["+my_idname+"]-某人(Someone.)");
                        send_msg = replace_string(send_msg, my_idname, "某人(Someone.)");
                        break;
                }
                else
                {

                        level_send_msg = replace_string(send_msg, my_idname, "["+my_idname+"]-穿幫的"+my_idname);
                        send_msg = replace_string(send_msg, my_idname, "穿幫的"+my_idname);
                }

                fit_users -= level_fit_users;
                         
                // 權限足夠之使用者
                //tell(level_fit_users, level_send_msg, CHNMSG);
                tell(level_fit_users, level_send_msg, "channel:"+channel); // 支持tomud
                
                level_fit_users->add_msg_log(channel, level_send_msg);
                SPECIAL_NPC->receive_report(me, channel);
        }

        //tell(fit_users, send_msg, CHNMSG);
        tell(fit_users, send_msg, "channel:"+channel); // 支持tomud        

        if( userp(me) && random(100) < 20 )
        {
                addn("active", 1, me);
                tell_object(me, HIY "\n由于您的踴躍發言讓笑傲江湖更加熱絡，特別為您增加活躍值一點。\n" NOR);
        }

        fit_users->add_msg_log(channel, send_msg);

        if( arrayp(ch->extra["listener"]) ) 
        {
                ch->extra["listener"] -= ({ 0 });
                if( sizeof(ch->extra["listener"]) )
                        ch->extra["listener"]->relay_channel(me, channel, msg);
        }
        
        switch(channel)
        {
        case "msg":
                break;
        case "chat":
        case "family":
        case "party":
        case "rumor":
        case "war":
        case "gwiz":
        case "sos":
        case "wiz":                
                if( !stringp(msg_log) ) msg_log = "";

                t = time();
                msg_log += sprintf(" %s\n%s",
                                log_time(),filter_color(send_msg));
                if( strlen(msg_log) > 8000 || t - log_from > 900 ) {
                        lt = localtime(t);

                        lfn = sprintf("channel/%d-%d-%d", lt[LT_YEAR],
                              lt[LT_MON] + 1, lt[LT_MDAY]);
                        assure_file(LOG_DIR + lfn);
                        log_file(lfn, msg_log);
                        msg_log = "";
                        log_from = t;
                }
                break;
        default:
                break;
        }
        return 1;
}

void register_relay_channel(string channel)
{
        class channel_class ch;
        object ob;
        ob = previous_object();
        ch = new(class channel_class);
        
        if( undefinedp(channels[channel]) || !ob )
                return;
        if( !classp(ch = channels[channel]) )
                return;
                
        if( arrayp(ch->extra["listener"]) ) {
                if( member_array(ob, ch->extra["listener"]) >= 0 )
                        return;
                ch->extra["listener"] += ({ ob });
        }
        else    ch->extra["listener"] = ({ ob });
}

/* 注冊頻道 */
nomask void register_channel(object me, int channel)
{
        if( !channel ) return;
        if( undefinedp(users[me]) ) users[me] = channel;
        else users[me] |= channel;
}

/* 移除注冊 */
nomask void remove_register(object me, int channel)
{
        if( !channel ) return;
        users[me] ^= channel;
        if( users[me] == 0 ) map_delete(users, me);
}

/* 直接移除一位使用者 */
nomask void remove_user(object me)
{
        map_delete(users, me);
}

/* 所有玩家重新注冊頻道 */
nomask void reset_all_register()
{
        users = allocate_mapping(0);
        filter_array( users(), (: register_channel($1, query("channels",$1)) :) );
}

nomask varargs string *query_channel_users(string channel, int flag)
{
        class channel_class ch;
        string *res = allocate(0);

        if( undefinedp(ch = channels[channel]) ) return res;
        foreach(object ob, int i in users)
        {
                if( !flag && (i & ch->number) ) res += ({ ob });
                if( flag && !(i & ch->number) ) res += ({ ob });
        }
        return res;
}

nomask int query_default_channel(string id)
{
        int default_channel=0, level = wiz_level(id);
        foreach( string name, class channel_class ch in channels )
        {
                if( level < ch->level ) continue;
                default_channel |= ch->number;
        }
        return default_channel &~ DEFAULT_REFUSE;
}

nomask varargs mixed query_using_channel(object user, int flag)
{
        int channel = users[user];
        string using_channel = "";
        string *using_ch = ({}); 

        if( channel )
                foreach( string name, class channel_class ch in channels )
                if( channel & ch->number )
                {
                        if( flag ) using_ch += ({ name });
                        else using_channel += " "+name;
                }
        
        if( flag ) return using_ch;
        return using_channel == "" ? "無" : using_channel;
}

varargs void channel_broadcast(string channel, string msg, mixed arg)
{
        switch(channel)
        {
        case "family":
                msg = NOR GRN"門派"+HIG+"新聞 "NOR+msg; break;
        case "party":
                msg = NOR CYN"幫派"+HIC+"新聞 "NOR+msg; break;
        default: break;
        }

        if( undefinedp(arg) )
                do_channel(this_object(), channel, msg, 1);
        else if( objectp(arg) )
                do_channel(arg, channel, msg, 1);
        else
                do_channel(this_object(),channel, msg, arg);

}

varargs void announce(object me, string msg)
{
        shout("\n\a"HIR + (objectp(me) ? me->query_idname() + HIR"發布":"") + "系統公告 ("HIW + ctime(time()) + NOR + HIR")：\n\n"NOR + msg + NOR"\n\n");
}


void create()
{
        class channel_class ch;

        if( clonep() ) destruct(this_object());
        
        seteuid(getuid());
        set("channel_id", "頻道精靈");
        
        channels = allocate_mapping(0);
        users = allocate_mapping(0);
        water_number = 10000;
        foreach( mixed *c in info )
        {
                ch = new(class channel_class);
                ch->number     = atoi(c[0]);
                ch->level      = atoi(c[2]);
                ch->msg        = c[3];
                ch->extra      = c[4];
                channels[c[1]] = ch;
        }
        reset_all_register();

}


string query_name()
{
        return "頻道系統(CHANNEL_D)";
}
