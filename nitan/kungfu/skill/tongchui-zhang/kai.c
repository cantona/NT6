#include <ansi.h>
#include <combat.h>

#define KAI "「" HIY "五丁開山" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/tongchui-zhang/kai", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(KAI "只能空手施展。\n");

        if ((int)me->query_skill("tongchui-zhang", 1) < 80)
                return notify_fail("你銅錘掌法不夠嫻熟，難以施展" KAI "。\n");

        if (me->query_skill_mapped("strike") != "tongchui-zhang") 
                return notify_fail("你沒有激發銅錘掌法，難以施展" KAI "。\n");

        if (me->query_skill_prepared("strike") != "tongchui-zhang") 
                return notify_fail("你沒有準備銅錘掌法，難以施展" KAI "。\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("你的內功修為不夠，難以施展" KAI "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不夠，難以施展" KAI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "右掌暗聚力道，十指分張，驀地一招「"
              HIR "五丁開山" HIY "」向$n" HIY "背心拍去。\n" NOR;

        if (random(me->query_skill("strike")) > target->query_skill("dodge") / 2)
        {
                damage = me->query_skill("strike");
                damage = damage / 3 + random(damage / 2);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                           HIR "結果$n" HIR "閃避不及，頓被$N" HIR
                                           "這掌擊個正中，五臟六腑翻騰不已。\n" NOR);
                me->start_busy(2);
                addn("neili", -80, me);
        } else
        {
                msg += CYN "可是$n" CYN "毫不慌張，當即向後輕"
                       "輕一躍，閃避開來。\n" NOR;
                me->start_busy(3);
                addn("neili", -30, me);
        }
        message_combatd(msg, me, target);

        return 1;
}