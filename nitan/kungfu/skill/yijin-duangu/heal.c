// This program is a part of NITAN MudLIB

#include <ansi.h>

#define HEAL "「" HIR "起死回生" NOR "」"

int exert(object me, object target)
{
        string force;

        if( userp(me) && !query("can_exert/yijin-duangu/heal", me) )
                return notify_fail("你所學的內功中沒有這種功能。\n");

        if (! target)
                return notify_fail("你要用真氣為誰療傷？\n");

        if (target == me)
                return notify_fail(HEAL "只能對別人施展。\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("戰鬥中無法運功療傷。\n");

        if( query("not_living", target) )
                return notify_fail("你無法給" + target->name() + "療傷。\n");

        if ((int)me->query_skill("yijin-duangu", 1) < 100)
                return notify_fail("你的易筋鍛骨不夠嫻熟，難以施展" HEAL "。\n");

        if (me->query_skill_mapped("force") != "yijin-duangu")
                return notify_fail("你沒有激發易筋鍛骨，難以施展" HEAL "。\n");
                
        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為太淺，難以施展" HEAL "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在的真氣不足，難以施展" HEAL "。\n");

        if( query("jing", me)<100 )
                return notify_fail("你現在的狀態不佳，難以施展" HEAL "。\n");

        if( query("eff_qi", target) >= query("max_qi", target) && 
            query("eff_jing", target) >= query("max_jing", target) )
                return notify_fail("對方沒有受傷，不需要接受治療。\n");

        message_sort(HIY "\n只見$N" HIY "默默運轉" + to_chinese(force) +
                     HIY "，深深吸進一口氣，頭上隱隱冒出白霧，陡然施展開"
                     "易筋鍛骨，以純陰內力瞬時點遍了$n" HIY "全身七十二"
                     "處大穴。過得一會，便見得$n" HIY "“哇”的一下吐出"
                     "幾口瘀血，臉色登時看起來紅潤多了。\n" NOR, me, target);

        addn("neili", -800, me);
        me->receive_damage("qi", 100);
        me->receive_damage("jing", 50);

        target->receive_curing("qi", 100 + (int)me->query_skill("force") +
                                     (int)me->query_skill("yijin-duangu", 1) * 3);

        if( query("qi", target) <= 0 )
                set("qi", 1, target);

        target->receive_curing("jing", 100 + (int)me->query_skill("force") / 3 +
                                       (int)me->query_skill("yijin-duangu", 1));

        if( query("jing", target) <= 0 )
                set("jing", 1, target);

        if ((int)target->query_condition("hamagong_poison"))
        {
                target->clear_condition("hamagong_poison");
                tell_object(target, HIC "\n你只覺體內殘存的蛤蟆功傷慢慢"
                                    "消退，感覺好多了。\n" NOR);
        }

        if (! living(target))
                target->revive();

        if (! target->is_busy())
                target->stary_busy(2);

        message_vision("\n$N閉目冥坐，開始運功調息。\n", me);
        me->start_busy(10);
        return 1;
}