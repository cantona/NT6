// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return CYN "雪鎖千山" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg, pmsg;
        string *limbs, limb;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("shentuo-zhang", 1) < 150)
                return notify_fail("你神駝雪山掌火候不夠，難以施展" +name()+ "。\n");

        if (me->query_skill_mapped("strike") != "shentuo-zhang")
                return notify_fail("你沒有激發神駝雪山掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "shentuo-zhang")
                return notify_fail("你沒有準備神駝雪山掌，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "一聲冷笑，掌勢一緩，一招「雪鎖千山」，掌上陰勁如怒"
              "濤洶湧，緩緩推向$n。\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                pmsg = HIR "霎時只聽「喀嚓」一聲脆響，$n" HIR "的"
                        "胸口肋骨竟然斷了幾根。\n" NOR;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45, pmsg);

                me->start_busy(1);
                addn("neili", -50, me);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$P"
                       CYN "的企圖，身形急動，躲開了這一掌。\n"NOR;
                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
