// This program is a part of NITAN MudLIB
// juan.c 卷字訣

#include <ansi.h>

inherit F_SSERVER;

string name() { return "卷字訣"; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("卷字訣只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if ((int)me->query_skill("xuantie-jian", 1) < 70)
                return notify_fail("你的玄鐵劍法不夠嫻熟，不能使用卷字訣。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，不能使用卷字訣。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在內力太弱，不能使用卷字訣。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("你沒有激發玄鐵劍法，不能施展卷字訣。\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N一抖手中的" + weapon->name() + HIY "，自下而上的朝$n"
              HIY "捲了過去，曲曲折折，變化無常！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                target->start_busy(ap / 80 + 2);
                addn("neili", -50, me);
                msg += YEL "$p" YEL "連忙竭力招架，一時無暇反擊。\n" NOR;
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，斜躍避開了$P"
                       CYN "的攻擊。\n"NOR;
                addn("neili", -25, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}