// top.c

#include <ansi.h>

inherit F_CLEAN_UP;

// 逆序排列(從高到低)
int sort_family(string f1, string f2, mapping fame)
{
        return fame[f2] - fame[f1];
}

// 逆序排列(從高到低)
int sort_league(string f1, string f2, mapping fame)
{
        return fame[f2] - fame[f1];
}

// 逆序排列(從高到低)
int sort_bunch(string f1, string f2, mapping fame)
{
        return fame[f2] - fame[f1];
}
int main(object me, string arg)
{
        mapping last, fame;
        array fam;
        string msg;
        int delta;
        int i;
        int cur_time;
        // 防止 flood add by ken@NT
        cur_time = time(); 
        if( cur_time-query_temp("last_who", me)<1){
              return notify_fail("系統氣喘噓地嘆道：慢慢來 ....\n"); 
        } 
        set_temp("last_who", cur_time, me);

        if (! arg || arg == "family")
        {
                fame = FAMILY_D->query_family_fame();
                last = FAMILY_D->query_all_last_family_fame();
        
                fam = keys(fame) - ({ 0 });
                fam = sort_array(fam, (: sort_family :), fame);
        
                msg = WHT "目前江湖上所有名門大派的聲望狀況\n" NOR
                      HIY "────────────────\n" NOR;
                for (i = 0; i < sizeof(fam); i++)
                {
                        delta = fame[fam[i]] - last[fam[i]];
                        msg += sprintf("%2d. %-12s  %-9d(%s%d%s)\n",
                                       i + 1, fam[i], fame[fam[i]],
                                       (delta > 0) ? HIY "+" :
                                       (delta < 0) ? HIR : WHT,
                                       delta, NOR);
                }
        
                msg += HIY "────────────────\n" NOR
                       WHT "一共是" + chinese_number(i) + "個門派。\n" NOR;
        } else
        if (arg == "league")
        {
                fame = LEAGUE_D->query_league_fame();
                last = LEAGUE_D->query_all_last_league_fame();
        
                fam = keys(fame) - ({ 0 });
                if (sizeof(fam) < 1)
                        return notify_fail("目前江湖上沒有什麼"
                                           "有名的結義同盟。\n");

                fam = sort_array(fam, (: sort_league :), fame);
        
                msg = WHT "目前江湖上著名結義同盟的聲望狀況\n" NOR
                      HIY "────────────────\n" NOR;
                for (i = 0; i < sizeof(fam) && i < 30; i++)
                {
                        delta = fame[fam[i]] - last[fam[i]];
                        msg += sprintf("%2d. %-12s  %-9d(%s%d%s)\n",
                                       i + 1, fam[i], fame[fam[i]],
                                       (delta > 0) ? HIY "+" :
                                       (delta < 0) ? HIR : WHT,
                                       delta, NOR);
                }
        
                msg += HIY "────────────────\n" NOR
                       WHT "列出了" + chinese_number(i) + "個結義同盟。\n" NOR;
        } else
        if (arg == "bunch")
        {
                fame = BUNCH_D->query_bunch_fame();
                last = BUNCH_D->query_all_last_bunch_fame();

                fam = keys(fame) - ({ 0 });
                if (sizeof(fam) < 1)
                        return notify_fail("目前江湖上沒有什麼"
                                           "有名的幫派。\n");

                fam = sort_array(fam, (: sort_bunch :), fame);

                msg = WHT "目前江湖上著名玩家幫派的聲望狀況\n" NOR
                      HIY "────────────────\n" NOR;
                for (i = 0; i < sizeof(fam) && i < 30; i++)
                {
                        delta = fame[fam[i]] - last[fam[i]];
                        msg += sprintf("%2d. %-12s  %-9d(%s%d%s)\n",
                                       i + 1, fam[i], fame[fam[i]],
                                       (delta > 0) ? HIY "+" :
                                       (delta < 0) ? HIR : WHT,
                                       delta, NOR);
                }

                msg += HIY "────────────────\n" NOR
                       WHT "列出了" + chinese_number(i) + "個幫派。\n" NOR;
        } else
                return notify_fail("你要看什麼排行榜？\n");

        write(msg);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: top [family | league | bunch]

查看目前江湖上大門派或是著名結義同盟或是幫派的排名狀況和相比去年變化
的程度。
HELP );
        return 1;
}

