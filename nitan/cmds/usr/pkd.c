// pkd.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object *obs;
        string msg;
        string sht;
        int i;

        if (PK_D->is_ready())
                return notify_fail("現在正在報名呢，等會兒再說。\n");

        obs = PK_D->query_all_competitor();
        if (! arrayp(obs) || ! sizeof(obs))
        {
                if (PK_D->is_pking())
                        return notify_fail("無法和 PK DAEMON 進行正常的聯系。\n");
                return notify_fail("現在屠人場內並沒有什麼人。\n");
        }

        obs -= ({ me, 0 });
        if (! sizeof(obs))
        {
                write("現在屠人場中只有你一個人了。\n");
                return 1;
        }

        msg = HIR "現在屠人場中除了你還剩下" + chinese_number(sizeof(obs)) +
              "人，他們是：\n" NOR;
        msg += HIC "≡" HIY "───────────────────────────────────" HIC "≡\n" NOR;
        for (i = 0; i < sizeof(obs); i++)
        {
                sht=obs[i]->name(1)+"("+query("id", obs[i])+")";
                msg+=(query("gender", obs[i]) == "女性"?HIC:WHT)+
                        sprintf("%-20s", sht) + NOR;
                if (! ((i + 1) % 4))
                        msg += "\n";
        }

        if (i % 4)
                msg += "\n";
        msg += HIC "≡" HIY "───────────────────────────────────" HIC "≡\n" NOR;
        write(msg);
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : pkd

用這條指令可以查看目前還有誰在屠人場中比賽。
 
HELP );
        return 1;
}