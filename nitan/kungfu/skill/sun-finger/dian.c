// This program is a part of NT MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "神指點穴" NOR; }

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

        if ((int)me->query_skill("sun-finger", 1) < 120)
                return notify_fail("你一陽指訣不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 120)
                return notify_fail("你對經絡學了解不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("你沒有激發一陽指訣，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("你沒有準備一陽指訣，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "凝聚一陽指訣功力，陡然點出一指，變化多端，巧逼$n"
              HIR "諸處大穴。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "被$P" HIR "逼得招"
                       "架不迭，一時無法反擊！\n" NOR;
                target->start_busy((int)me->query_skill("finger") / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的變化，"
                       "小心招架，擋住了$P" CYN "的進擊。\n" NOR;

        }
        me->start_busy(2);
        message_combatd(msg, me, target);

        return 1;
}
