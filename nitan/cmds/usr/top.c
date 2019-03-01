// This program is a part of NT MudLIB
// Written by Lonely@nitan.org

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

string help = @HELP
列出各種排行榜：

top gaoshou             - 世界高手排行榜
top average             - 世界高手練功速度排行榜
HELP;

int top_list(object ob1,object ob2);
int get_score(object ob);
int top_average(object ob1, object ob2);
string *get_average(object ob);
int main(object me, string arg)
{

        object *list,*ob;
        int i, n;
        string msg;
        string arg1, arg2, arg3;
        string *res;

        if( time()-query_temp("last_top", me)<10 )
              return notify_fail("系統氣喘噓地歎道：慢慢來 ....\n");

        if( !wizardp(me) )
                set_temp("last_top", time(), me);

        if( !arg )
                return notify_fail(help);

        if( sscanf(arg, "%s %s %s", arg1, arg2, arg3) == 3 )
        {
                if( arg3 == "all" )
                        n = 200;
                else
                        n = to_int(arg3);
        }
        else if( sscanf(arg, "%s %s", arg1, arg2) == 2 )
        {
                if( arg2 == "all" )
                        n = 200;
                else if( to_int(arg2) )
                {
                        n = to_int(arg2);
                        arg2= 0;
                }
                else
                        n = 30;
        }
        else
        {
                n = 10;
                arg1 = arg;
        }

        if( n < 1 || n > 200 )
                return notify_fail("顯示排名數量不得小於 1 或大於 200。\n");

        switch( arg1 )
        {
        case "average":
                if( !wizardp(me) ) return notify_fail("練功狂人排名查詢功能不對玩家開放。\n");
                msg = NOR YEL"世界"HIY"前 "+n+" 練功狂人"NOR YEL"排行榜：\n"NOR;
                msg += NOR WHT"────────────────────────────────────────\n"NOR;
                msg += sprintf(HIW"%4s %-28s %-12s %12s %12s\n"NOR, "排名", "玩家", "經驗", "潛能", "體會");
                msg += NOR WHT"────────────────────────────────────────\n"NOR;

                ob = filter_array(users(), (: playerp($1) && living($1) && !wizardp($1) :));
                list = sort_array(ob, (: top_average :));
                for (i = 0 ;i < n ; i++)
                {
                        if( i >= sizeof(list))
                                msg += sprintf("│  %-5s 暫時空缺。　　　　　　　　　　　　　　　│\n"NOR,chinese_number(i+1));
                        else {
                                res = query_temp("average", list[i]);
                                if( list[i] == me ) msg += BBLU HIY;
                                msg+=sprintf("│%-5s%-22s%-12d%12d%12d│\n"NOR,chinese_number(i+1),query("name", list[i])+"("+
                                                        capitalize(query("id", list[i]))+")",
                                                        res[0],
                                                        res[1],
                                                        res[2]);
                        }
                }
                msg += "└───巫師、斷線、睡眠、昏迷均不進入排名榜───┘\n";
                msg += "  " + NATURE_D->game_time() + "記。\n";
                write(msg);
                break;
        case "gaoshou":
                ob = filter_array(users(), (: playerp($1) && living($1) && !wizardp($1) :));
                list = sort_array(ob, (: top_list :));
                msg = HIR "\n\t  ======== 笑傲江湖在線高手排行榜 ========\n" NOR;
                msg += HIR "\t  /                                      \\\n" NOR;   
                msg += sprintf(HIY "%-10s%-20s%-22s%-20s\n" NOR, "高手排名", "尊姓大名", "所屬門派", "評價");
                msg += HIM "---------------------------------------------------------------\n"NOR;
                for (i = 0 ;i < n ; i++)
                {
                        if( i >= sizeof(list))
                                msg += sprintf(HIW"   %-7s 暫時空缺。　　　　　　　　　　　　　　　\n"NOR,chinese_number(i+1));
                        else {
                                if( list[i] == me ) msg += BBLU HIY;
                                msg+=sprintf(HIW"   %-7s%-20s%-22s%-20s\n"NOR,chinese_number(i+1),query("name", list[i])+"("+
                                                        capitalize(query("id", list[i]))+")",
                                                        query("family/family_name", list[i])?list[i]->query_family():"普通百姓",
                                                        "不便透露");
                        }
                }
                msg += HIM "---------------------------------------------------------------\n"NOR;
                msg += HIR "\t  \\                                      /\n" NOR;
                msg += HIR "\t  ========================================\n" NOR;
                msg += HIC + NATURE_D->game_time() + "記。\n" NOR;
                write(msg);
                break;
        default:
                write(help);
                break;
        }
        return 1;

}

int top_list(object ob1, object ob2)
{
        int score1,score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

        return score2 - score1;
}

int get_score(object ob)
{
        int tlvl,i,score;
        string *ski;
        mapping skills;

        reset_eval_cost();

        skills = ob->query_skills();
        if (!sizeof(skills)) return 1;
        ski  = keys(skills);
        for(i = 0; i<sizeof(ski); i++) {
                tlvl += skills[ski[i]];
        }  // count total skill levels
        score = tlvl/1;
        score+=query("max_neili", ob)/1;
        score += ob->query_str() + ob->query_int() + ob->query_dex() + ob->query_con();
        score+=query("combat_exp", ob)/10+query("reborn/times", ob)*1000000000;

        return score;
}

int top_average(object ob1, object ob2)

{
        string *score1, *score2;

        score1 = get_average(ob1);
        score2 = get_average(ob2);

        return to_int(score2[0]) - to_int(score1[0]);
}

string *get_average(object ob)
{
        int dexp, dpot, dmar, dt;
        string *res;

        dexp = query("combat_exp", ob) - query("last_examine/combat_exp", ob);
        dpot = query("potential", ob) - query("last_examine/potential", ob);
        dmar = query("experience", ob) - query("last_examine/experience", ob);
        dt = time() - query("last_examine/time", ob);
        res = ({ dexp * 60 / dt, dpot * 60 / dt, dmar * 60 /dt });
        set_temp("average", res, ob);
        return res;
}

