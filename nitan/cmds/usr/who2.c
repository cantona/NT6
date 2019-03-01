//CMDS USR who.c
//Created by waiwai@2000/10/18 重新建立
//Last modified by waiwai@2001/07/05

#include <ansi.h>
#include <net/dns.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

int sort_user(object,object);

void create() { seteuid(getuid()); }

mixed main(object me, string arg, int remote)
{
        string str,load,cmds,comp, *option, fname = "";
        object *list, *ob,ob1;
        int i, t_ppl_cnt, cnt, count, wcnt = 0;
        int opt_long, opt_id, opt_wiz, opt_party,opt_male,opt_female;

        if( !wizardp(me) && userp(me) ){
        if( uptime()-me->query_temp("last_who_time")<5)
                return notify_fail(WHT"你正忙著。\n"NOR);
        }
        me->set_temp("last_who_time",uptime());

        if( arg ) {
                option = explode(arg, " ");
                i = sizeof(option);
                while( i-- )
                        switch(option[i]) {
                                case "-l": opt_long = 1; break;
                                case "-i": opt_id = 1; break;
                                case "-w": opt_wiz = 1; break;
                                case "-p": opt_party = 1; break;
                                default:
                                        if (!ob1 ) ob1 = find_player(option[i]);
                                        if (!ob1) ob1 = find_living(option[i]);
                                        if ((!ob1) && (option[i] =="me")) ob1=me;
                                        if (!ob1) return notify_fail("沒有這個玩家或參數錯誤。\n指令格式 : who [i] [-l] [-w] [-p] [<ID>]\n");
                                        if (!ob1 || wizardp(ob1) ) return notify_fail("沒有這個玩家或參數錯誤。\n指令格式 : who [-i] [-l] [-w] [-p] [<ID>]\n");
                                        me = ob1; opt_party = 1;

                                        if( wizardp(me)
                                        &&      option[i][0]=='@' ) {
                                                RWHO_Q->send_rwho_q(option[i][1..sizeof(option[i])],
                                                        me, opt_long);
                                                write("網路訊息已送出，請稍候。\n");
                                                return 1;
                                        }

                                        return notify_fail("指令格式：who [-l|-i|-w|-p]\n");
                        }
        }

        if( opt_long && !wizardp(me)) {
                if( (int)me->query("sen") < 20 )
                        return notify_fail("你的精神太差了，沒有辦法得知所有玩家的詳細資料。\n");
                me->receive_damage("sen", 20);
        }

        str = HIR"★"HIW+MUD_NAME+HIW" 目前";
        if(opt_party)
                if(me->query("family/family_name"))
                        str += HIG+me->query("family/family_name")+HIW"的玩家有：";
                else str += "在線"HIC"普通百姓"HIW"有：";
        else if(opt_wiz)
                str += "在線"HIR"巫師"HIW"有：";
        else if(opt_long) str += "玩家有：";

        else str += "在線玩家有：";

     str += NOR"\n□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n"NOR;
        ob = filter_array(objects(), (: userp :));
        if (opt_party)
                ob = filter_array(ob, (: $1->query("family/family_name") ==
                        $2->query("family/family_name") :), me);
        list = sort_array(ob, (: sort_user :));
        t_ppl_cnt = 0;
        cnt = 0;
        if( opt_long || opt_wiz ) {
                i = sizeof(list);
                while( i-- ) {
                        // Skip those users in login limbo.
                        if( !environment(list[i]) ) continue;
                        if( !me->visible(list[i]) ) continue;
            if( opt_wiz && !wiz_level(list[i]) ) continue;
                        if (interactive(list[i])) t_ppl_cnt++;
                        else cnt++;
                        str = sprintf("%s%12s%s%s\n",
                                str,
                                RANK_D->query_rank(list[i]),
                                interactive(list[i])?(query_idle(list[i]) > 180?HIM "*"NOR:" "):HIR "#" NOR,
                                list[i]->short(1)
                        );
                }
        } else {
                i = sizeof(list);
                count = 0;
                while( i-- ) {
                        // Skip those users in login limbo.
                        if( !environment(list[i]) ) continue;
                        if( !me->visible(list[i]) ) continue;
                        if (!wiz_level(list[i]) && fname != list[i]->query("family/family_name")) {
                            fname = list[i]->query("family/family_name");
                            if (count % 7) str += "\n";
                            str += sprintf( "%-15s" NOR, (fname?fname:"普通百姓") + "：");
                            count = 1;
                        }
                        if (!wcnt && wiz_level(list[i])) {
                            if (count % 7) str += "\n";
                            str += sprintf(HIY "%-15s" NOR, "巫    師：");
                            wcnt = 1;
                            count = 1;
                        }
                        if (!(count%7)) {
                                count++;
                                str += "               ";
                        }
                        str = sprintf("%s%s%s%-9s"NOR"%s",
                                str,
                                interactive(list[i])?(query_idle(list[i]) > 180?HIM "*"NOR:" "):HIR "#"NOR,
                                list[i]->query("nopk")?BBLU +"":NOR+"",
                                opt_id?capitalize(list[i]->query("id")): list[i]->name(1),
                                ++count%7 ? "": "\n"
                        );
                        if (interactive(list[i])) t_ppl_cnt++;
                        else cnt++;
                }
                if( count%7 ) str += "\n";
        }
   str += "□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n"NOR;
 
         load=query_load_average();

        if(sscanf(load,"%s cmds/s, %s comp lines/s", cmds,comp)!=2) {
                str = sprintf("%s有 %d 位玩家連線中，%d 位玩家斷線中，系統執行速率：%s \n"HIR"#"NOR" 表示斷線中  "HIM"*"NOR" 表示發呆中"NOR,
                str, t_ppl_cnt,cnt, load);
                } else {
                str = sprintf("%s共有 %d 位玩家連線中，%d 位斷線中,"+
                        "平均每秒執行 %s 條指令"+
                        ((!remote&&userp(me))?"，編譯 %s 行源程序":"")+
                        "\n"HIR"#"NOR" 表示斷線中  "HIM"*"NOR" 表示發呆中\n"NOR,
                        str, t_ppl_cnt, cnt,cmds, comp);
        }

        if( remote ) return str;

        me->start_more(str);
        return 1;
}

int sort_user(object ob1, object ob2)
{
        string name1, name2;

        reset_eval_cost();
        if( wiz_level(ob1) != wiz_level(ob2) )
                return wiz_level(ob2) - wiz_level(ob1);
        
        name1 = ob1->query("family/family_name");
        name2 = ob2->query("family/family_name");

        if (intp(name1)) name1 = "";
        if (intp(name2)) name2 = "";
        if (name1 > name2) return -1;
        if (name1 < name2) return 1;

        return (int)ob2->query("combat_exp") - (int)ob1->query("combat_exp");
}

int help(object me)
{
write(@HELP

指令格式 : who [-l|-i|-w|-p]

這個指令可以列出所有在線上的玩家及其狀態。

-l 選項列出較長的訊息
-i 只列出玩家的英文代號
-p 只列出同門的玩家
-w 只列出在線巫師

相關指令： finger

HELP
        );
        return 1;
}

