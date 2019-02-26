// who.c
// From ES2

#include <ansi.h>
#include <net/dns.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

//#define PREFIX(ob)    (ob->is_chatter() ? HIC "~" : interactive(ob) ? (query_idle(ob) > 120 ? HIG "*" NOR : " ") : stringp(query("doing", ob)) ? HIY "@" NOR : HIR "#" NOR)
#define PREFIX(ob)    (ob->is_chatter() ? HIC "~" : interactive(ob) ? (query_idle(ob) > 120 ? HIG "*" NOR : " ") : stringp(query("doing", ob)) ? HIY " " NOR : HIR "#" NOR) 

int sort_user(object,object);
int sort_user_by_name(object, object, int d);
int help();

void create() { seteuid(getuid()); }

mixed main(object me, string arg, int remote)
{
        string name, str, *option;
        object *list, *ob, ob1;
        int i, ppl_cnt;
        int opt_interactive;
        int opt_long, opt_wiz, opt_party;
        int opt_chatter, opt_player;
        int opt_male, opt_female, opt_sort;
        int opt_family, opt_number;
        int opt_master;
        int opt_closed;
        int opt_reborn;
        int cur_time;
        int opt_employ;
        
        object vob;
        string who_name;
        string who_id;

        vob = me;
        opt_chatter = 1;
        opt_player = 1;
        who_name = 0;
        
        cur_time = time(); 
        if( !wizardp(me) && cur_time-query_temp("last_who", me)<5 )
        {
              return notify_fail("系統氣喘噓地歎道：慢慢來 ....\n"); 
        } 
        set_temp("last_who", cur_time, me);


        if (arg)
        {
                if (arg == "我愛笑傲江湖")
                {
                        str = "";
                        ob = users();
                        i = sizeof(ob);
                        while ( i -- )
                        {
                                if ( !ob[i] )
                                        continue;
                                if (! me->visible(ob[i]))
                                        continue;
                                if( !environment(ob[i]) && !query_temp("waiting_enter", ob[i]) )
                                {
                                        destruct(ob[i]);//有點危險
                                        continue;
                                }
                                str += ADD2(ob[i]);
                        }

                        write(CLEAN2+str);
                        return 1;
                }

                option = explode(arg, " ");
                i = sizeof(option);
                while (i--)
                        switch (option[i])
                        {
                                case "-h": return help();
                                case "-l": opt_long = 1;        break;
                                case "-w": opt_wiz = 1;         break;
                                case "-p": opt_party = 1;       break;
                                case "-fam": opt_family = 1;    break;
                                case "-f": opt_female = 1;      break;
                                case "-m": opt_male = 1;        break;
                                case "-c": opt_chatter = 1; opt_player = 0;     break;
                                case "-r": opt_player = 1; opt_chatter = 0;     break;
                                case "-u": opt_master = 1;      break;
                                case "-i":
                                case "-s": opt_sort = 1;        break;
                                case "-S": opt_sort = -1;       break;
                                case "-z": opt_reborn = 1;       break;
                                case "-n": opt_number = 1;      break;
                                case "-@": opt_closed = 1;      break;
                                case "-!": opt_interactive = 1; break;
                                case "-v": opt_employ = 1; MYGIFT_D->check_mygift(me, "newbie_mygift/who"); break;
                                default:
                                        if (wizardp(me) &&
                                            option[i][0] == '@')
                                        {
                                                RWHO_Q->send_rwho_q(option[i][1..sizeof(option[i])],
                                                                    me, opt_long);
                                                write("網路訊息已送出，請稍候。\n");
                                                return 1;
                                        }

                                        if (i > 0 && option[i - 1] == "is")
                                        {
                                                who_name = option[i];
                                                i--;
                                                break;
                                        }

                                        if (! me) break;
                                        if (environment(me))
                                                ob1 = present(option[i], environment(me));
                                        if (! ob1 || ! me->visible(ob1))
                                                ob1 = find_player(option[i]);
                                        if (! ob1 || ! me->visible(ob1))
                                                ob1 = find_living(option[i]);
                                        if (! ob1 || ! me->visible(ob1))
                                                return notify_fail("沒有這個玩家或參數錯誤。\n指令格式 : who [-h] [-l] [-w] [-p] [-fam] [-m] [-f] [<ID>]\n");
                                        if( !query("family/family_name", ob1) )
                                                return notify_fail(ob1->name(1) + "現在還沒有加入任何一個門派。\n");

                                        me = ob1;
                                        opt_family = 1;
                        }
        }

        if (opt_male && opt_female)
        {
                write("參數 -f 和 -m 不能同時使用。\n");
                return 1;
        }

        if (opt_long && me && (vob == this_player()) && ! wizardp(me) && ! remote)
        {
                if( query("jing", me)<5 )
                        return notify_fail("你的精神太差了，沒有辦法得知其他玩家的詳細資料。\n");
                me->receive_damage("jing", 5);
        }

        if (opt_player) ob = users(); else ob = ({ });
        if (opt_chatter && sizeof(MESSAGE_D->query_connection()))
                ob += filter_array(values(MESSAGE_D->query_connection()),
                                   (: objectp :));

        if (opt_party)
        {
                if( !query("bunch/bunch_name", me) )
                        return notify_fail("你現在還沒有加入任何一個幫派。\n");
                ob=filter_array(ob,(:query("bunch/bunch_name", $1) == 
                        query("bunch/bunch_name", $2):),me);
        }

        if (opt_family)
        {
                if( !query("family/family_name", me) )
                        return notify_fail("你現在還沒有加入任何一個門派。\n");
                       ob=filter_array(ob,(:query("family/family_name", $1) == 
                        query("family/family_name", $2):),me);
        }

        if (opt_male)
                       ob=filter_array(ob,(:query("gender", $1) == "男性":));

        if (opt_female)
                       ob=filter_array(ob,(:query("gender", $1) == "女性":));

        if (who_name)
        {
                str = WHT + NAME_D->who_is(who_name) + "\n" NOR;
                ob = filter_array(ob, (: $1->name(1) == $(who_name) :));
        } else
                str = "";

        if (opt_wiz)
                ob = filter_array(ob, (: wizardp :));

        if (objectp(vob))
                ob = filter_array(ob, (: $(vob)->visible($1) :));
        else
                ob=filter_array(ob,(:query("env/invisible", $1):));

        if (opt_master)
                ob = filter_array(ob, (: ultrap :));

        if (opt_closed)
        {
                if( !wizardp(me) ) return notify_fail("沒有這個玩家或參數錯誤。\n指令格式 : who [-h] [-l] [-w] [-p] [-fam] [-m] [-f] [<ID>]\n");
                ob=filter_array(ob,(:!interactive($1) && query("doing", $1):));
        }

        if (opt_interactive)
        {
                if( !wizardp(me) ) return notify_fail("沒有這個玩家或參數錯誤。\n指令格式 : who [-h] [-l] [-w] [-p] [-fam] [-m] [-f] [<ID>]\n");
                ob = filter_array(ob, (: interactive($1) :));
        }

        if (opt_reborn)
                ob=filter_array(ob,(:query("reborn/times", $1):));

        if (! sizeof(ob))
        {
                str += "泥潭中現在沒有符合條件的玩家。\n";
                if (remote) return str;
                write(str);
                return 1;
        }

        str += HIG "◎" + LOCAL_MUD_NAME() + HIG "◎" + NOR WHT + "  目前江湖中的";
        if (opt_party)
        {
                if( query("bunch/bunch_name", me) )
                        str += HIR + " (" + query("bunch/bunch_name", me) + ") " + NOR WHT;
                else    str += HIC + " (無幫派) " + NOR WHT;
        } else
        if (opt_family)
        {
                if( query("family/family_name", me) )
                        str+=HIR+"("+query("family/family_name", me)+")"+NOR+WHT;
                else    str += HIC + " (無門派) " + NOR WHT;
        }

        if (! who_name)
                who_name = "";
        else
                who_name = "(" + who_name + ")";

        if (opt_closed)
                str += "修煉中的";

        if (opt_reborn)
                str += "轉世重生";

        if (opt_wiz)
                str += (opt_female ? "女性" : opt_male ? "男性" : "") +
                       "巫師" + who_name + "有：";
        else
                if (opt_long) str += (opt_female ? "女性" : opt_male ? "男性" : "") +
                                     (opt_master ? "大宗師" : "玩家") + who_name + "有：";
                else str += (opt_female ? "女性" : opt_male ? "男性" : "") +
                            (opt_master ? "大宗師" : "玩家") + who_name + "有：";

        if (opt_employ)
                str += "<在線的新手導師有>:";

        if (opt_number)
        {
                str += chinese_number(sizeof(ob)) + " 人。\n";
                if (remote) return str;
                write(str);
                return 1;
        }

        str += NOR"\n"HIC"≡" + HIY"─────────────────────────────────────"HIC"≡\n"NOR;

        if (opt_employ)     
        {
                object *virep_ob = ({ });
                mapping db;
                object cob, eob;
                string *virlist;
                
                for (i = 0; i < sizeof(ob); i++)
                {
                        cob = ob[i];
                        
                        if (query("viremploy/job", cob))
                        {
                                virep_ob += ({ cob });
                        }
                        continue;       
                }
                list = ({ });
                list = virep_ob;
                ppl_cnt = 0;
               
                str += NOR + HIC "≡" + HIY " 新手導師 " + HIC + "≡\n" NOR; 
                ppl_cnt++;
                i = sizeof(list);
                while (i--)
                {
                        if (query("viremploy/job", list[i]) == "新手導師")
                        {
                                ppl_cnt++;
                                str = sprintf("%s%12s%s%s\n",
                                str,
                                RANK_D->query_rank(list[i]),
                                PREFIX(list[i]),
                                list[i]->short(1));
                         }
                }
                
                if ((query("viremploy/job", me) == "新手導師" || wizardp(me)) && sizeof(virlist = DB_D->query_data("virlist/teacher")))
                {
                        str += NOR + HIC "\n≡"  + HIM "遊戲中所有在職導師" + HIC + "≡\n" NOR; 
                        for (i = 0; i < sizeof(virlist);i ++)
                        {
                                if (find_player(virlist[i]))
                                {
                                        str += HIY + find_player(virlist[i])->name() + HIY + "(" + virlist[i] + ")--在線\n";
                                }
                                else
                                {
                                        eob = UPDATE_D->global_find_player(virlist[i]);
                                        if( !objectp(eob) ) continue; 
                                        str += HIY + eob->name() + HIY + "(" + virlist[i] + ") --離線時間：" + NOR;
                                        str += HIY + sprintf("%d", (time() - query("last_on", eob)) / 86400) + "天\n" NOR;
                                        UPDATE_D->global_destruct_player(eob, 1);
                                        
                                }
                        }
                }
                
                /*
                ppl_cnt++;
                str += NOR "\n" HIC "≡" + HIY " 遊戲宣傳 " + HIC + "≡\n\n" NOR;
                ppl_cnt++;
                i = sizeof(list);
                while (i--)
                {
                        if (query("viremploy/job", list[i]) == "遊戲宣傳")
                        {                        
                                ppl_cnt++;
                                str = sprintf("%s%12s%s%s\n",
                                        str,
                                        RANK_D->query_rank(list[i]),
                                        PREFIX(list[i]),
                                        list[i]->short(1));
                        }
                }
                */
                
        } 
        else
        {
        if (opt_sort)
                list = sort_array(ob, (: sort_user_by_name :), opt_sort);
        else
        {
                // Why I sort the array use too many variable ?
                // Only optimize for speed :)
                // The normal_ob store the ob without family
                // the wiz_ob story the wizards
                // the mapping familys story all the others
                // & why I create generation ? becuase I want
                // to sort the player in one family by the
                // generation, but I won't directly sort them
                // use function:query, it too slow.
                mapping familys = ([ ]);
                mapping generation = ([ ]);
                object *normal_ob = ({ }), *wiz_ob = ({ });
                mapping db;
                mapping fam;
                string fam_name;
                object cob;
                mixed val;
                
                for (i = 0; i < sizeof(ob); i++)
                {
                        cob = ob[i];
                        if (wizardp(cob))
                        {
                                wiz_ob += ({ cob });
                                continue;
                        }

                        db = cob->query_entire_dbase();
                        if (! mapp(fam = db["family"]) ||
                            ! stringp(fam_name = fam["family_name"]))
                        {
                                normal_ob += ({ cob });
                                continue;
                        }

                        if (! arrayp(familys[fam_name]))
                                familys[fam_name] = ({ cob });
                        else
                                familys[fam_name] += ({ cob });
                        generation[cob] = fam["generation"];
                }

                list = ({ });
                for (i = 0; i < sizeof(val = values(familys)); i++)
                        list += sort_array(val[i], (: $(generation)[$1] -
                                                      $(generation)[$2] :));
                list = wiz_ob + list + normal_ob;
        }

        ppl_cnt = 0;
        if (opt_long)
        {
                i = sizeof(list);
                while (i--)
                {
                        // Skip those users in login limbo.
                        ppl_cnt++;
                        str = sprintf("%s%12s%s%s\n",
                                str,
                                RANK_D->query_rank(list[i]),
                                PREFIX(list[i]),
                                list[i]->short(1));
                }
        } else
        {
                i = sizeof(list);
                while (i--)
                {
                        int len;
                        // Skip those users in login limbo.
                        who_id=query("id", list[i]);
                        if (! stringp(who_id))
                                who_id = "#" + geteuid(list[i]);
                        name = sprintf("%s%s%-10s(%-12s",
                                        PREFIX(list[i]),
                                        wizardp(list[i])?HIY:query("gender", list[i]) == "女性"?HIM:NOR+WHT,
                                        list[i]->name(1),
                                        capitalize(who_id)+")");
                        /*
                        len = color_len(list[i]->query_idname(1));
                        name = sprintf("%s%s%-" + (22 + len) + "s" NOR,
                                        PREFIX(list[i]),
                                        wizardp(list[i])?HIY:query("gender", list[i]) == "女性"?HIM:NORWHT,
                                        list[i]->query_idname(1));
                        */

                        str = sprintf("%s%s%s", str, name,
                                      ppl_cnt%3==2?"\n": HIY"│");
                        ppl_cnt++;
                }
                if (ppl_cnt % 3) str += "\n";
        }
        }

        str += HIC"≡"+HIY"─────────────────────────────────────"HIC"≡\n"NOR;
        str = sprintf("%s共有 %s 位使用者連線中，系統負擔：%s\n "
                      HIG "*" NOR " 表示發呆中，" HIC "~" NOR " 表示聊天中，"
                      HIR "#" NOR " 表示斷線中，"HIY"@" NOR" 表示離線修煉中。\n",
                      str, CHINESE_D->chinese_number(ppl_cnt),
                      query_load_average());

        if (remote) return str;
        me->start_more(str);
        return 1;
}

int sort_user_by_name(object ob1, object ob2, int d)
{
        if (wizardp(ob1) && ! wizardp(ob2)) return -1;
        if (wizardp(ob2) && ! wizardp(ob1)) return 1;
        if (wizardp(ob1) && wizardp(ob2))
                return (int)SECURITY_D->get_wiz_level(ob2) 
                        - (int)SECURITY_D->get_wiz_level(ob1);

        return strcmp(query("id", ob2),query("id", ob1))*d;
}

int help()
{
        write("
指令格式 : who [-h] [-l] [-w] [-p] [-c] [-fam] [-f] [-m] [-s] [-S] [-z] [<ID>] [-n] [is <中文名字>]

這個指令可以列出所有在線上的玩家及其等級。

-h   列出幫助屏幕。
-l   選項列出較長的訊息。
-p   只列出同幫派的玩家。
-fam 只列出同門派的玩家。
-w   只列出線上所有的巫師。
-c   只列出正在聊天的玩家。
-m   只列出江湖中的男性玩家。
-f   只列出江湖中的女性玩家。
-u   只列出江湖中的大宗師們。
-!   只列出江湖中正在連線的玩家
-@   只列出江湖中正在離線修煉的玩家。
-s   按照ID字母升序排列所有的玩家
-S   按照ID字母降序排列所有的玩家
-z   只列出江湖中的轉世重生的玩家。
-v   只列出江湖中是新手導師的玩家。
-n   只列出當前符合查找條件的玩家的數目。
<ID> 列出<ID>代表玩家所屬門派的玩家。
is   如果使用了這個選項，後面要跟隨玩家的中文名字。

"HIG"*"NOR" 表示"HIG"發呆"NOR"中，"HIC "~"NOR" 表示聊天中，"
HIR"#"NOR" 表示"HIR"斷線"NOR"中，"HIY"@"NOR" 表示"HIY"離線修煉"NOR"中。

相關指令： finger
" );
        return 1;
}
