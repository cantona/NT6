// tell.c

#include <ansi.h>
#include <net/dns.h>
#include <net/messaged.h>
#include <mudlib.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

int notice_user(string my_name, string my_id, object obj, string tell_out);
int help(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string target, msg, mud;
        object obj;
        string no_tell, can_tell;
        mapping m,o;
        //string tell_out;
        m=me->query_entire_dbase();
        if(m["chblk_on"]&&!wizardp(me))
                return write(ALERT("你的頻道被關閉了，在你試圖發出任何信息前請先與江湖小豬聯繫。\n"));
        if (! arg || sscanf(arg, "%s %s", target, msg) != 2)
                return help(me);

        if (sscanf(target, "%s@%s", target, mud) == 2)
        {
                if (GTELL->send_gtell(mud, target, me, msg))
                {
                        write(MTEXT("網路訊息已送出，可能要稍候才能得到迴應。\n"));
                        return 1;
                }
        }

        obj = find_player(target);
        if (! obj || ! me->visible(obj))
        {
                if (MESSAGE_D->send_msg_to(me, target, msg))
                        return 1;
                return notify_fail(ALERT("這個俠客沒有登錄，你無法與其交談！\n"));
        }
        o=obj->query_entire_dbase();
        no_tell=query("env/no_tell", obj)+"";
        if (! wizardp(me) && (lower_case(no_tell) == "all" || no_tell == "全部" || is_sub(m["id"], no_tell) || is_sub(m["name"],no_tell) ))
        {
                can_tell=query("env/can_tell", obj);
                if (! is_sub(m["id"], can_tell) && ! is_sub(m["name"],can_tell))
                        return notify_fail(ALERT("對方把你列入黑名單啦，聽不到你的話的。\n"));
        }
        if( o["doing"]=="neili" )
                return notify_fail(ALERT("此人正在練功。\n"));
        if ( !interactive(obj) || obj->is_net_dead()  )//要將離線攢內除外
                return notify_fail(ALERT("此人現在不在線上，聽不到你的話。\n"));

        if (! living(obj))
                return notify_fail(ALERT("這人現在恐怕聽不到你説的話了...\n"));

        if (me->ban_say(1))
                return 0;

        if (obj == me)
        {
                message_vision(MTEXT("$N喃喃自語。\n"), me);
                return 1;
        }

        if (! notice_user(m["name"], m["id"], obj, msg))
                return 1;

        if (query_idle(obj) >= 120)
                write(ALERT( "\n可是" + o["name"] +
                       "已經在豬圈中發呆有" + chinese_number(query_idle(obj) / 60) +
                      "分鐘了，恐怕沒法立刻回答你。\n"));

        return 1;
}

string remote_tell(string cname, string from, string mud, string to, string msg, int wiz_level)
{
        object ob;
        string fromid;
        string no_tell;
        string can_tell;
        string tell_out;

        if (ob = MESSAGE_D->find_user(to))
        {
                if( query("env/invisible", ob) )
                        return "這個人現在不在線上。";

                fromid = lower_case(from + "@" + mud);
                no_tell=query("env/no_tell", ob);
                if ((! intp(wiz_level) || wiz_level < 3) &&
                    (no_tell == "all" || no_tell == "ALL" ||
                     is_sub(fromid, no_tell)))
                {
                        can_tell=query("env/can_tell", ob);
                        if (! is_sub(fromid, can_tell))
                                return "這個人不想聽你羅嗦啦。";
                }

                fromid = capitalize(from) + "@" + upper_case(mud);
                msg = replace_string(msg, "\n", "");
                if (cname)
                        tell_out = sprintf(HIG "%s(%s)告訴你：%s\n" NOR,
                                           cname, fromid, msg);
                else
                {
                        cname = "未知";
                        tell_out = sprintf(HIG "%s 告訴你：%s\n" NOR,
                                           fromid, msg);
                }

                to = capitalize(to);
                if (! notice_user(cname, fromid, ob, tell_out))
                        msg = sprintf(HIG "你的話沒有送到%s(%s@%s)的耳邊。\n" NOR,
                                      ob->name(1), to, upper_case(INTERMUD_MUD_NAME));
                else
                        msg = sprintf(HIG "你告訴%s(%s@%s)：%s" NOR, ob->name(1), to,
                                      upper_case(INTERMUD_MUD_NAME), msg);
                return msg;

        } else
                return "這個人現在不在線上。";
}

// 將消息送給對方
int notice_user(string my_name, string my_id, object obj, string tell_out)
{
        int i;
        mixed info;
        mixed *list;
        mixed piece;
//        string ico;
        object me;
        if(!objectp(me=this_player()))
                return 1;
        tell_out=replace_string(tell_out,"$","");
        tell_out=replace_string(tell_out,TMA,"");
        tell_out=replace_string(tell_out,TMB,"");
        tell_out=TMI("ctellname="+my_name+";ID="+my_id+";icon="+query("icon", me)+";"+tell_out);
        if( query("env/jam_talk", obj) )
        {
                // 阻塞式交談
                info = ({ my_name, my_id, tell_out });
                list=query_temp("tell_list", obj);
                if (! arrayp(list) || sizeof(list) < 1)
                {
                        // 對方沒有阻塞消息，直接通知對方
                        tell_object(obj, tell_out);
                        set_temp("reply", my_id, obj);
                        list = ({ info });
                } else
                if (arrayp(list[0]) && sizeof(list[0]) >= 3 &&
                    list[0][1] == my_id)
                {
                        // 對方阻塞的正是和我交談的信息，所以
                        // 這條信息就沒有必要延遲發送了
                        tell_object(obj, tell_out);
                } else
                {
                        // 遍歷所有的歷史信息，查看是否已經有
                        // 交談的記錄了
                        for (i = 1; i < sizeof(list); i++)
                        {
                                piece = list[i];
                                if (! arrayp(piece) || sizeof(piece) < 3 ||
                                    ! stringp(piece[2]))
                                {
                                        // 這條歷史記錄不合法
                                        list[i] = 0;
                                        continue;
                                }

                                if (piece[1] == my_id)
                                {
                                        // 找到了和對方以前交談的信息
                                        if (strlen(piece[2]) > 32768)
                                        {
                                                // 歷史信息已經過了32K了
                                                write(MTEXT("你已經説了好多話了，先等別人聽完吧。\n"));
                                                return 0;
                                        }

                                        // 記錄這次交談的信息
                                        piece[2] += tell_out;
                                        info = 0;
                                }
                        }
                        list -= ({ 0 });

                        // 這個人還有沒有聽完的話呢
                        if (arrayp(info))
                        {
                                if (sizeof(list) > 12)
                                {
                                        write(MTEXT(obj->name(1) + "耳邊已經有太多"
                                              "的話了，你還是等會兒再説吧。\n"));
                                        return 0;
                                }

                                // 記錄這句話
                                list += ({ info });
                                if (! in_input(obj))
                                        obj->write_prompt();
                        }
                }
                set_temp("tell_list", list, obj);
        } else
        {
                // 正常聊天
                set_temp("reply", my_id, obj);
                tell_object(obj, tell_out);
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：tell <某人> <訊息>

你可以用這個指令和其他地方的使用者説話。如果對方選擇阻塞式交
談，那麼他可能不會立刻聽到你説的話。

其他相關指令：reply、skip
HELP );
        return 1;
}