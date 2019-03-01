// qdel.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping total;
        object *obs, *dst;
        object qob;

        seteuid(getuid());

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return notify_fail("你要清除什麼任務？\n");

        total=query("information", get_object(QUEST_D));
        if (! mapp(total))
                return notify_fail("當前系統沒有任何任務。\n");

        obs = keys(total);
        obs = filter_array(obs, (: objectp($1) :));

        if (! sizeof(obs))
                return notify_fail("當前系統沒有任何任務。\n");

        sscanf(arg, "%s %*s", arg);
        if (arg == "all" || arg == "ALL")
        {
                foreach (qob in obs)
                {
                        reset_eval_cost();
                        destruct(qob);
                }
                write("你清除了系統中所有的任務。\n");
                return 1;
        }

        qob = find_object(arg);
        if (! objectp(qob) || ! qob->is_quest())
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

        write("你清除了『" + qob->name() + "』這個任務。\n");
        destruct(qob);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : qdel all | <任務名稱>

此指令可清除當前系統某一個任務或是所有的任務。
HELP
        );
        return 1;
}
