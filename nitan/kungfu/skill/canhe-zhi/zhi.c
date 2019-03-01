// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "七星指穴" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int skill;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        skill = me->query_skill("canhe-zhi", 1);

        if (skill < 120)
                return notify_fail("你的參合指修為有限，難以施展" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "canhe-zhi")
                return notify_fail("你沒有激發參合指, 難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "canhe-zhi")
                return notify_fail("你現在沒有準備使用參合指, 難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "$N" HIG "一聲冷哼，右手中食兩指並攏，斜斜指出，朝$n"
              HIG "凌空虛點七下。\n" NOR;

        addn("neili", -120, me);

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "結果只聽“噗噗噗”數聲，$p" HIR "竟被$P"
                       HIR "以指力封住穴道，動彈不得。\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，輕輕一躍，躲開了這一招。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}