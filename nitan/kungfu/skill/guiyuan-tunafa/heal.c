// heal.c

#include <ansi.h>

int exert(object me, object target, int amount)
{
        if( me->is_fighting() )
                return notify_fail("戰鬥中運功療傷？找死嗎？\n");

        if( query("neili", me)-query("max_neili", me)<50 )
                return notify_fail("你的真氣不夠。\n");

        if( query("eff_qi", me)<query("max_qi", me)/2 )
                return 
notify_fail("你已經受傷過重，只怕一運真氣便有生命危險！\n");

        write( HIW "你全身放鬆，坐下來開始運功療傷。\n" NOR);
        message("vision",
                HIW + me->name() + 
"坐下來運功療傷，臉上一陣紅一陣白，不久，吐出一口瘀血，臉色看起來好多了。\n" 
NOR,
                environment(me), me);

        me->receive_curing("qi", 10 + (int)me->query_skill("force")/5 );
        addn("neili", -50, me);
        set("force_factor", 0, me);
        me->start_busy(2);
        return 1;
}
 