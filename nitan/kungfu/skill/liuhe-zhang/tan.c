#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "烏龍探海" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name()+"只能空手施展。\n");

        if ((int)me->query_skill("liuhe-zhang", 1) < 60)
                return notify_fail("你的六合掌法不夠嫻熟，難以施展"+name()+"。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，難以施展"+name()+"。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，難以施展"+name()+"。\n");

        if (me->query_skill_mapped("strike") != "liuhe-zhang")
                return notify_fail("你沒有激發六合掌法，難以施展"+name()+"。\n");

        if (me->query_skill_prepared("strike") != "liuhe-zhang")
                return notify_fail("你沒有準備六合掌法，難以施展"+name()+"。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "履步沉身，雙肩蓄力，陡然間單掌颼的探出，一招「烏龍"
              "探海勢」向$n" HIC "胸前拍落！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");

                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "結果$p" HIR "閃避不及，被$P" HIR
                                           "一掌拍在胸口，頓時口噴鮮血，幾乎昏厥"
                                           "！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -30, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}