// lifeheal.c

#include <ansi.h>

int exert(object me, object target)
{
        string force;

        if (! target || target == me)
                return notify_fail("你要用真氣為誰療傷？\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("戰鬥中無法運功療傷！\n");

        if( query("not_living", target) )
                return notify_fail("你不能給" + target->name() + "療傷。\n");

        force = me->query_skill_mapped("force");
        if (! force)
                return notify_fail("你必須激發一種內功才能替人療傷。\n");

        if ((int)me->query_skill(force,1) < 50)
                return notify_fail("你的" + to_chinese(force) + "等級不夠。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力修為不夠。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在的真氣不夠。\n");

        if( query("eff_qi", target) >= query("max_qi", target) )
                return notify_fail( target->name() +
                        "現在沒有受傷，不需要你運功治療！\n");

        if( query("eff_qi", target)<query("max_qi", target)/5 )
                return notify_fail( target->name() +
                        "已經受傷過重，經受不起你的真氣震盪！\n");

        message_vision(
                HIY "$N坐了下來運起" + to_chinese(force) +
                "，將手掌貼在$n背心，緩緩地將真氣輸入$n體內....\n"
                HIW "過了不久，$N額頭上冒出豆大的汗珠，$n吐出一"
                "口瘀血，臉色看起來紅潤多了。\n" NOR,
                me, target );

        target->receive_curing("qi", 10 + (int)me->query_skill("force") / 2);
        addn("qi", 10+me->query_skill("force")/3, target);
        if( query("qi", target)>query("eff_qi", target) )
                set("qi",query("eff_qi",  target), target);

        addn("neili", -150, me);
        return 1;
}