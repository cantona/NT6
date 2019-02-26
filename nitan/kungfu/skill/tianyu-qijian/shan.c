// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "閃劍訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("tianyu-qijian", 1) < 60)
                return notify_fail("你的天羽奇劍不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "身子微動，手腕一探，頓時一道劍光至劍尖透出，疾電般"
              "射向$n" HIW "。\n" NOR;
        addn("neili", -80, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "$n" HIR "大吃一驚，慌忙招架，這一下便失了先機。\n" NOR;
                target->start_busy(ap / 100 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "不慌不忙，看破了此招"
                       "虛實，並沒有受到半點影響。\n" NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
