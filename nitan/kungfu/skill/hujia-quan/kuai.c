// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return WHT "奔拳快打" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不足，難以施展" + name() + "。\n");

        if ((int)me->query_skill("hujia-quan", 1) < 80)
                return notify_fail("你的胡家拳法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "hujia-quan")
                return notify_fail("你沒有激發胡家拳法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "hujia-quan")
                return notify_fail("你沒有準備胡家拳法，難以施展" + name() + "。\n");

        if( query("neili", me)<80 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "縱步上前，拳招迭出，疾如奔雷，霎時已向$n" WHT "攻出數拳。\n" NOR;

        addn("neili", -40, me);
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$n" HIR "無法分清$N" HIR "招式中的虛實，"
                       "不由手忙腳亂。\n" NOR;
                target->start_busy(ap / 120 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的虛招，輕輕一閃，"
                       "避開了這驟雨般的拳影。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
