#include <ansi.h>
#include <combat.h>

#define BAO "「" HIW "蛟龍抱" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/dulong-shenzhua/bao", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(BAO "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(BAO "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("dulong-shenzhua", 1) < 80)
                return notify_fail("你毒龍神爪功不夠嫻熟，難以施展" BAO "。\n");

        if (me->query_skill_mapped("claw") != "dulong-shenzhua")
                return notify_fail("你沒有毒龍神爪功，難以施展" BAO "。\n");

        if (me->query_skill_prepared("claw") != "dulong-shenzhua")
                return notify_fail("你沒有準備毒龍神爪功，難以施展" BAO "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，難以施展" BAO "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" BAO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = me->query_skill("dulong-shenzhua", 1) +
             me->query_skill("dodge", 1) / 2;

        dp = target->query_skill("dodge");

        msg = HIC "\n$N" HIC "尖嘯一聲，雙爪齊出，施出絕招「" HIW "蛟龍抱" HIC "」，"
              "雙爪猶如蛟龍般將$n" HIC "纏住。\n" NOR;

        message_sort(msg, me, target);
        
        if (random(ap) > dp / 2)
        {
                msg = HIR "$n" HIR "心神懼裂，一時間竟無從應對。\n" NOR;
                target->start_busy(ap / 36 + 1);
                       me->start_busy(1);
                addn("neili", -160, me);
        } else
        {
                msg = CYN "$n" CYN "看破$N" CYN "毫無攻擊之意，於"
                      "是大膽反攻，將$N" CYN "這招盡數化解。\n" NOR;

                me->start_busy(2);
                addn("neili", -60, me);
        }
        message_vision(msg, me, target);

        return 1;
}