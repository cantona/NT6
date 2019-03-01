// cost.c
// updated by doing

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping before, after;
        int eval_cost;
        mapping info, linfo;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(getuid());
           if (! arg) return notify_fail("指令格式：cost <指令> [<參數> ....]\n");

        info = rusage();
        eval_cost = eval_cost();
        me->force_me(arg);
        eval_cost -= eval_cost();
        linfo = rusage();

        write(sprintf(WHT "Eval cost：%d 單位  CPU time = %d+%d 毫秒\n" NOR,
                      eval_cost,
                      linfo["utime"] - info["utime"],
                      linfo["stime"] - info["stime"]));
        return 1;
}

int help()
{
        write( @TEXT
指令格式：cost <指令> [<參數> .... ]

這個指令讓你測量另一個指令執行所需的時間。
TEXT );
        return 1 ;
}