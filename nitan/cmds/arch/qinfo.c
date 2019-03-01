// qinfo.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

string time_len(int n)
{
        return sprintf("%.2d:%.2d:%.2d", n / 3600, (n % 3600) / 60, n % 60);
}

int main(object me, string arg)
{
        mapping total;
        object *obs;
        object qob;
        string str;

        seteuid(getuid());

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        total=query("information", get_object(QUEST_D));
        if (! mapp(total))
                return notify_fail("當前系統沒有任何任務。\n");

        obs = keys(total);
        obs = filter_array(obs, (: objectp($1) :));

        if (! sizeof(obs))
                return notify_fail("當前系統沒有任何任務。\n");

        if (arg)
        {
                sscanf(arg, "%s %*s", arg);
                qob = find_object(arg);
                if (! objectp(qob) || member_array(qob, obs) == -1)
                {
                        obs = filter_array(obs, (: $1->name() == $(arg) :));
                        if (! sizeof(obs))
                        {
                                write("目前系統中不存在 " + arg +
                                      " 這個任務。\n");
                                return 1;
                        }
                        qob = obs[0];
                }

                write(sprintf("有關任務 " + qob->name() + " 的情報信息：\n%O\n",
                              total[qob]));
                return 1;
        }

        str = WHT "任務名稱              執行時間    狀  態    任務對象對應的系統OBJECT\n" NOR
              HIW "──────────────────────────────────\n" NOR;
        foreach (qob in obs)
        {
                str += sprintf("%-22s%-12s%-10s%s\n",
                               qob->name(),
                               time_len(time()-query("start_time", qob)),
                               qob->query_status(),
                               file_name(qob));
        }
        str += HIW "──────────────────────────────────\n" NOR
               WHT "系統目前共有 " CYN + sizeof(obs) + WHT " 個任務。\n" NOR;

        me->start_more(str);

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : qinfo [<任務名稱>]

此指令可查看當前系統有的任務。
HELP );
        return 1;
}
