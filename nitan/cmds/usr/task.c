 // task.c

#include <ansi.h>
int main(object me, string str)
{
        string output;

        if( me->is_busy() )
                return notify_fail("你現在正忙。\n");

        if( !wizardp(me) && (time()-query_temp("last_tasks", me)<5) )
                return notify_fail("系統氣喘噓地歎道：慢慢來 ....\n");  

        if( query("jing", me)<2 )
                return notify_fail("你現在精神狀態不佳，還是等會再查吧。\n");

        addn("jing", -2, me);

        if (str && str == "count")
        {
                tell_object(me,"你目前已經完成有效TASK使命"+query("task/count", me)+"個。\n");
                return 1;
        }

    output = HIR"★ "HIW"泥潭"HIR" ★"HIG" TASK任務 使命榜\n" NOR; 
    output += ""HIW"─────────────────────────────────────\n"NOR"";   
        output += TASK_D->task_list();   
    output += ""HIW"─────────────────────────────────────\n\n"NOR"";   

        me->start_more(output);
        set_temp("last_tasks", time(), me);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: task
指令格式: task count 查看自己已經完成TASK使命的個數。
相關文件: help tasks

這個指令是用來得知目前的所有使命.

HELP
        );
        return 1;
}
