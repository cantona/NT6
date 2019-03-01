#include <ansi.h>
#include <combat.h>

string name() { return HIW "冷劍決" NOR; }

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

        if (me->query_skill("force") < 50)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("hanmei-jian", 1) < 40)
                return notify_fail("你的寒梅劍法修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "hanmei-jian")
                return notify_fail("你沒有激發寒梅劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "輕吁一聲，飛身一躍而起，手中" + weapon->name() +
              HIW "攜著陰寒之勁刺向$n" HIW "！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -30, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "結果$n" HIR "一個不慎，頓被$N" HIR
                                           "一劍劃出道寸許長的傷口！\n" NOR);
        } else
        {
                addn("neili", -10, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "並不慌亂，收斂心神，輕輕格擋開了$P"
                       CYN "的劍招。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}