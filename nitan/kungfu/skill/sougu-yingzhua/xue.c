// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "赤血爪" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (query_temp("weapon", me) || query_temp("secondary_weapon", me))
                return notify_fail(name() + "只能空手施展。\n");

         if ((int)me->query_skill("sougu-yingzhua", 1) < 60)
                return notify_fail("你搜骨鷹爪功不夠嫻熟，難以施展" + name() + "。\n");

       if (me->query_skill_mapped("claw") != "sougu-yingzhua")
                return notify_fail("你沒有激發搜骨鷹爪功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("claw") != "sougu-yingzhua")
                return notify_fail("你沒有準備毒搜骨鷹爪功，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 80)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if ((int)query("neili", me) < 220)
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        msg = HIW "\n$N" HIW "運轉真氣，雙手忽成爪行，施出絕招「" HIR "赤"
              "血爪" HIW "」，迅猛無比地抓向$n" HIW "。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "claw");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIR "但見$N" HIR "雙爪劃過，$n" HIR "已閃避不及，胸口被$N" HIR
                                           "抓出十條血痕。\n" NOR);

                me->start_busy(3);
                addn("neili", -200, me);
        } else
        {
                msg += CYN "$n" CYN "奮力招架，竟將$N" CYN "這招化解。\n" NOR;

                me->start_busy(4);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}


