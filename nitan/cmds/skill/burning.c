// burning.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        int count;

        if( query_temp("burning_up", me) )
                return notify_fail("你現在正在怒火中，沒有必要再發作一次。\n");

        if (me->query_craze() < 1000)
                return notify_fail("你現在還不夠憤怒，無法讓自己怒火燃燒。\n");

        message_vision(HIR "$N" HIR "一聲大吼，兩目登時精光"
                       "四射，咄咄逼人，勢不可擋。\n" NOR, me);

        me->cost_craze(500 + random(300));
        count = me->query_skill("force") / 5;
        set_temp("burning_up", count, me);
        addn_temp("apply/attack", count, me);
        me->apply_condition("burning", 1);

        return 1;
}

int help (object me)
{
        write(@HELP
指令格式: burning|fenu

這個指令讓你將現在將積蓄的憤怒發泄出來，這樣可以充分的提升你
的攻擊能力。在發泄時會不斷的消耗你的憤怒，直到心情平靜的時候
才自動恢復。

HELP
        );
        return 1;
}