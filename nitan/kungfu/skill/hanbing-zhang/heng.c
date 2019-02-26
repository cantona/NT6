#include <ansi.h>
#include <combat.h>

#define HENG "「" HIG "踏雪無痕" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/hanbing-zhang/heng", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HENG "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HENG "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("hanbing-zhang", 1) < 100)
                return notify_fail("你寒冰掌不夠嫻熟，難以施展" HENG "。\n");

        if (me->query_skill_prepared("strike") != "hanbing-zhang")
                return notify_fail("你沒有準備寒冰掌，難以施展" HENG "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，難以施展" HENG "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在的真氣不夠，難以施展" HENG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = me->query_skill("hanbing-zhang", 1) +
             me->query_skill("dodge", 1) / 2;

        dp = target->query_skill("dodge");

        msg = HIC "\n$N" HIC "怒喝一聲，施出絕招「" HIG "踏雪無痕" HIC 
              "」剎時間，寒意襲捲漫天，但見$N" HIC "雙掌連續反轉，不斷"
              "拍向$n" HIC "，竟將$n" HIC "困在掌風之下。\n" NOR;
        message_sort(msg, me, target);
        
        if (random(ap) > dp / 2)
        {
                msg = HIR "$n" HIR "心中一驚，一時間竟無從應對，"
                      "竟被困在$N" HIR "的掌風之中。\n" NOR;

                target->start_busy(ap / 40 + 2);
                       me->start_busy(1);
                addn("neili", -100, me);
        } else
        {
                msg = CYN "$n" CYN "看破$N" CYN "毫無攻擊之意，於"
                      "是大膽反攻，將$N" CYN "這招盡數化解。\n" NOR;

                me->start_busy(2);
                addn("neili", -30, me);
        }
        message_vision(msg, me, target);

        return 1;
}