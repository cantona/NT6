// lifeheal.c

#include <ansi.h>

int exert(object me, object target)
{
        if( !target || !target->is_character() || target == me )
                return notify_fail("你要用真氣為誰療傷？\n");

        if( me->is_fighting() || target->is_fighting())
                return notify_fail("戰鬥中無法運功療傷！\n");

        notify_fail("不是你要抓的人，湊什麼熱鬧！\n");
        if (!userp(target) && !target->accept_hit(me)) return 0;

        if( me->is_busy() )
                return notify_fail("你現在正忙着呢，哪有空運功？\n");

        if( target->is_busy())
                return notify_fail(target->name()+"現在正忙着呢！\n");

        if( (int)me->query_skill("linji-zhuang",1) < 20 )
                return notify_fail("你的臨濟十二莊修為不夠。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力修為不夠。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真氣不夠。\n");
/*
        if( query("eff_qi", target) >= query("max_qi", target) )
                return notify_fail( target->name() + "只是累了，沒有受傷，不必勞起你的真氣療傷！\n");
*/
        if( query("eff_qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() + "已經受傷過重，經受不起你的真氣震盪！\n");

        message_combatd( HIY "$N坐了下來運起內功，將手掌貼在$n背心，緩緩地將真氣輸入$n體內....\n\n過了不久，$N額頭上冒出豆大的汗珠，$n吐出一口瘀血，臉色看起來紅潤多了。\n" NOR, me, target );

        target->receive_curing("qi", 10 + (int)me->query_skill("force")/2 );
        addn("qi", 10+me->query_skill("force")/3, target);
        if( query("qi", target)>query("eff_qi", target) )
                set("qi",query("eff_qi",  target), target);

        addn("neili", -50, me);
        me->start_busy(1);
        if ( userp(target)) target->start_busy(2);

        return 1;
}

int help(object me)
{
        write(WHT"\n臨濟十二莊之他療："NOR"\n");
        write(@HELP

        使用功效：
                為他人療傷

        出手要求：
                臨濟十二莊20級
                內力100
HELP
        );
        return 1;
}
