// This program is a part of NITAN MudLIB
// feng.c 破玉拳「封閉手」

#include <ansi.h>

string name() { return HIG "封閉手" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if ((int)me->query_skill("poyu-quan", 1) < 60)
                return notify_fail("你的劈石破玉拳不夠嫻熟，不會使用" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "poyu-quan")
                return notify_fail("你沒有準備使用劈石破玉拳，無法施展" + name() + "。\n");

        if( query("neili", me)<80 )
                return notify_fail("你現在真氣不夠，無法施展" + name() + "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "\n只見$N" HIC "左掌虛探，右拳颼的一聲從掌風中\n"
              "猛穿過來，正是劈石破玉拳法的絕招之一「" HIG "封閉手" HIC "」。\n" NOR;

        addn("neili", -40, me);
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "運力招架，一時卻覺得"
                       "內力不濟，被$P" HIR "搶住手腕一拉，頓時立足"
                       "不穩，滴溜溜打了兩個圈子。\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "奮力一架，硬生生格開了$P"
                       CYN "這一拳。\n" NOR;
                me->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}
