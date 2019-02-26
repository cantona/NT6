// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "天外流星" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (me->query_skill("force") < 180)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("liuxing-jianfa", 1) < 120)
                return notify_fail("你的流星劍法修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "liuxing-jianfa")
                return notify_fail("你沒有激發流星劍法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$n" HIY "驀地眼前光華大盛，$N" HIY "手中" + weapon->name() + HIY
              "活像從天外飛來的流星，只奔$n" HIY "而去，那一瞬間的光芒和速度，沒有一件事能阻擋。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -150, me);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$n" HIR "尚未反應，已被$N" HIR "手中的" + weapon->name() +
                                           HIR "當胸搠中，鮮血飛濺！\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -60, me);

                msg += CYN "可是$p" CYN "並不慌亂，收斂心神，輕輕格擋開了$P"
                       CYN "的劍招。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
