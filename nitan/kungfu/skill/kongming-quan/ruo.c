#include <ansi.h>

string name() { return HIG "空明若玄" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int level;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((level = me->query_skill("kongming-quan", 1)) < 100)
                return notify_fail("你的空明拳不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "kongming-quan")
                return notify_fail("你沒有激發空明拳，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "kongming-quan")
                return notify_fail("你沒有準備空明拳，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣太弱，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "使出空明拳「" HIG "空明若玄" NOR + WHT "」，雙手"
              "吞吐不定，運轉如意，試圖擾亂$n" WHT "的攻勢。\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "unarmed");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "結果$n" HIR "被$N" HIR "的拳招所牽制，招架"
                       "不迭，全然無法反擊！\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，鎮定逾"
                       "恆，全神應對自如。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
