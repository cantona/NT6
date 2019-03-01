// wakeup.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>

int exert(object me, object target)
{
        if( (!target) || query("id", target) == query("id", me) )
                return notify_fail("你要用真氣救醒誰？\n");
/*
        if( me->is_fighting() || target->is_fighting())
                return notify_fail("戰鬥中無法運功救人！\n");
*/
        if(target == me)
                return notify_fail("你不能為自己救醒自己！\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你的真氣不夠。\n");

        if( query("eff_qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() +
                        "已經受傷過重，經受不起你的真氣震盪！\n");

        message_combatd(HIY "$N坐了下來運起內功，將手掌貼在$n背心，緩緩地將真氣輸入$n體內....\n\n過了不久，$N額頭上冒出豆大的汗珠，$n吐出一口瘀血，臉色看起來紅潤多了。\n$n慢慢的蘇醒過來。\n" NOR, me, target );

        target->receive_curing("qi", 10 + (int)me->query_skill("force")/3 );
        addn("qi", 10+me->query_skill("force")/3, target);
        if( query("qi", target)>query("eff_qi", target))set("qi",query("eff_qi",  target), target);

           target->remove_call_out("revive");
           target->revive();
           target->reincarnate();
 
        addn("neili", -150, me);
        set("jiali", 0, me);
//                me->start_busy(5);
//                target->start_busy(5);
        return 1;
}