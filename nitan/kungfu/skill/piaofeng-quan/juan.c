#include <ansi.h>

#define JUAN "「" HIW "卷字決" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/piaofeng-quan/juan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(JUAN "只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");
                
        if ((int)me->query_skill("piaofeng-quan", 1) < 30)
                return notify_fail("你的飄風拳法不夠嫻熟，不會使用" JUAN "。\n");

        if (me->query_skill_prepared("cuff") != "piaofeng-quan")
                return notify_fail("你沒有準備使用飄風拳法，無法施展" JUAN "。\n");

        if( query("neili", me)<80 )
                return notify_fail("你現在真氣不夠，無法施展" JUAN "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "\n只見$N" HIC "右拳直出，中途猛地一轉，突然發力，身法"
              "陡快，將$n" HIC "籠罩， 正是飄風拳法絕招「" HIW "卷字決" HIC "」。\n" NOR;

        addn("neili", -40, me);
        if (random(me->query_skill("cuff")) > (int)target->query_skill("force") / 2)
        {
                msg += HIR "結果$p" HIR "運力招架，一時卻覺得"
                       "內力不濟，被$P" HIR "搶住手腕一拉，頓時立足"
                       "不穩，滴溜溜打了兩個圈子。\n" NOR;
                target->start_busy((int)me->query_skill("cuff") / 22);
        } else
        {
                msg += CYN "可是$p" CYN "奮力一架，硬生生格開了$P"
                       CYN "這一拳。\n" NOR;
                me->start_busy(1);
        }
        message_sort(msg, me, target);

        return 1;
}