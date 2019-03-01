#include <ansi.h>
#include <combat.h>

string name() { return HIM "鶴沖九霄" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("yunhe-jian", 1) < 100)
                return notify_fail("你的雲鶴七劍修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "yunhe-jian")
                return notify_fail("你沒有激發雲鶴七劍，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIM "$N" HIM "陡然一聲長嘯，手中" + weapon->name() +
              HIM "疾射而出，勾勒出一道絢麗的劍芒，直劃$n" HIM "前胸！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -80, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 35,
                                           HIR "$n" HIR "奮力格擋，終究不敵，被$N"
                                           HIR "一劍刺中胸口，鮮血飛濺而出！\n" NOR);
        } else
        {
                addn("neili", -60, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "並不慌亂，收斂心神，輕輕格擋開了$P"
                       CYN "的劍招。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}