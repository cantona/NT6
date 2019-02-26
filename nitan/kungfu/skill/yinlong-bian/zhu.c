#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "天誅龍蛟訣" NOR; }

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
            query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if (me->query_skill("force", 1) < 130)
                return notify_fail("你的內功火候不夠，使不了" + name() + "。\n");

        if (me->query_skill("yinlong-bian", 1) < 100)
                return notify_fail("你的銀龍鞭法功力太淺，使不了" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，無法使用" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "yinlong-bian")
                return notify_fail("你沒有激發銀龍鞭法，使不了" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "詭異的一笑，手中" + weapon->name() +
              HIW "猶如一條銀龍猛然飛向$n" HIW "，正是九陰真經中的"
             "絕招「" HIC "天誅龍蛟訣" HIW "」！\n" NOR;

        ap = attack_power(me, "whip") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -200, me);
                me->start_busy(2);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 85,
                                           HIR "結果$n" HIR "一聲慘叫，未能看破$N"
                                           HIR "的企圖，被這一鞭硬擊在胸口，鮮血飛"
                                           "濺，皮肉綻開！\n" NOR);
                message_combatd(msg, me, target);

        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "可是$p" CYN "飛身一躍而起，躲避開了"
                       CYN "$P" CYN "的攻擊！\n" NOR;
                message_combatd(msg, me, target);
        }

        return 1;
}