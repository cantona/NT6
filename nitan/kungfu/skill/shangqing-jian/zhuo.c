#include <ansi.h>
#include <combat.h>

string name() { return WHT "濁流劍" NOR; }

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

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("shangqing-jian", 1) < 140)
                return notify_fail("你的上清劍法修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "shangqing-jian")
                return notify_fail("你沒有激發上清劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "只見$N" WHT "手中" + weapon->name() + WHT "一抖，施出上清劍法"
              "「濁流劍」，霎時無數劍光罩向$n" WHT "！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -100, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$n" HIR "只感劍光奪目，頓時眼花繚"
                                           "亂，被$N" HIR "一劍刺中，鮮血飛濺。\n"
                                           NOR);
        } else
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN "可是$n" CYN "看破" CYN "$N"
                       CYN "的招數，飛身一縱，避開了這"
                       "一劍。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}