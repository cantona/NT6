// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "奪魂勢" NOR; }

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

        if (me->query_skill("chanhun-suo", 1) < 100)
                return notify_fail("你的纏魂索功力太淺，使不了" + name() + "。\n");

        if( query("neili", me)<220 )
                return notify_fail("你的真氣不夠，無法使用" + name() + "。\n");

        if (me->query_skill_mapped("whip") != "chanhun-suo")
                return notify_fail("你沒有激發纏魂索法，使不了" + name() + "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "詭異的一笑，手中" + weapon->name() +
              HIY "抖得筆直，劈向$n" HIY "手腕，可是待到中途卻又停滯，轉往$n"
              HIY "胸口揮去！\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "whip");
                addn("neili", -180, me);
                me->start_busy(2);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           HIR "結果$n" HIR "一聲慘叫，未能看破$N"
                                           HIR "的企圖，被這一鞭硬擊在胸口，鮮血飛"
                                           "濺，皮肉綻開！\n" NOR);
                message_combatd(msg, me, target);
                // if (ap > 1000) ap = 1000;
                dp += target->query_skill("martial-cognize", 1) * 2;
                if (! target->is_busy() &&
                    query("material", weapon) == "white silk" &&
                    ap / 2 + random(ap) > dp)
                {
                        target->start_busy(3 + random(4));
                        message_vision(HIW "$N" HIW "一抖，手中的" + weapon->name() +
                                       HIW "“嗖“的串了出來，隱隱然纏向$n"
                                       HIW "。\n$n" HIW "大吃一驚，急忙退後，閃去這一招。\n" NOR,
                                       me, target);
                }
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