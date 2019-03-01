#include <ansi.h>
#include <combat.h>

string name() { return HIM "孤雁出群" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("tongbi-zhang", 1) < 80)
                return notify_fail("你通臂六合掌不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "tongbi-zhang")
                return notify_fail("你沒有準備通臂六合掌，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 80)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<120 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");

        msg = HIC "\n$N" HIC "騰空而起，施展出絕招「" HIM "孤雁出群" HIC "」，"
              "猶如一只大雁臨空而下，雙掌猛地拍向$n" HIC "。\n" NOR;
        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage , 35,
                                           HIR "但見$N" HIR "雙掌拍來，掌風作響，"
                                           "當真迅捷無比。$n" HIR "頓覺心驚膽戰，\n"
                                           "毫無招架之力，微作遲疑間$N" HIR "這掌"
                                           "已正中$n" HIR "胸口，頓將$p震退數步。"
                                           " \n" NOR);

                me->start_busy(1 + random(2));
                addn("neili", -80, me);
        } else
        {
                msg = CYN "$n" CYN "見$N" CYN "這掌拍來，內力"
                      "充盈，只得向後一縱，才躲過這一掌。\n" NOR;

                me->start_busy(3);
                addn("neili", -100, me);
        }
        message_combatd(msg, me, target);
        return 1;
}