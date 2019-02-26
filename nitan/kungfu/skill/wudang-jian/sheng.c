#include <ansi.h>
#include <combat.h>

string name() { return HIW "太極初升" NOR; }

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

        if (me->query_skill("force") < 80)
                return notify_fail("你的內功的修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill("wudang-jian", 1) < 60)
                return notify_fail("你的武當劍法修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "wudang-jian")
                return notify_fail("你沒有激發武當劍法，難以施展" + name() + "。\n");

        if( query("neili", me)<50 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "凝神聚氣，手中" + weapon->name() +
              HIW "迴轉，劃出一個閃亮的劍圈，套向$n" HIW "而去。\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -30, me);
                me->start_busy(2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "不明劍理，一個不慎，登時被$N"
                                           HIR "劃中，鮮血直流！\n" NOR);
        } else
        {
                addn("neili", -20, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "微微一笑，輕輕格擋開了$P"
                       CYN "的劍招。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}