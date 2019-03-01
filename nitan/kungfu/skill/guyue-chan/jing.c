#include <ansi.h>
#include <combat.h>

string name() { return HIY "皓月驚空 " NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, wn;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "staff" )
                return notify_fail("你所使用的武器不對，難以施展" + name() + "。\n");

        if ((int)me->query_skill("guyue-chan", 1) < 80)
                return notify_fail("你孤月鏟法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("staff") != "guyue-chan")
                return notify_fail("你沒有激發孤月鏟法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<600 )
                return notify_fail("你的內力修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        wn = weapon->name();

        msg = HIW "$N" HIW "怒喝一聲，將手中的" + wn + HIW "揮舞得呼呼做響，"
              "猛然間向$n" HIW "砸去。\n" NOR;

        ap = attack_power(me, "staff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "staff");
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$n" HIR "只覺眼花繚亂，想閃避已不及，"
                                           "被" + wn + HIR "打中胸口，頓時噴出一口鮮"
                                           "血。\n" NOR);
                me->start_busy(2);
                addn("neili", -80, me);
        } else
        {
                msg += CYN "$n" CYN "見$N" CYN "這招剛猛無比，不敢硬接，只得\n"
                       "側身一跳才躲過這招。\n"NOR;
                me->start_busy(3);
                addn("neili", -200, me);
        }

        message_combatd(msg, me, target);
        return 1;
}