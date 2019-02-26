#include <ansi.h>
#include <combat.h>

#define YING "「" HIY "無影掌" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/songyang-zhang/ying", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YING "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(YING "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("songyang-zhang", 1) < 100)
                return notify_fail("你嵩陽掌不夠嫻熟，難以施展" YING "。\n");

        if (me->query_skill_prepared("strike") != "songyang-zhang")
                return notify_fail("你沒有準備嵩陽掌，難以施展" YING "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，難以施展" YING "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" YING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = me->query_skill("songyang-zhang", 1) +
             me->query_skill("dodge", 1) / 2;

        dp = target->query_skill("dodge");

        msg = HIC "\n$N" HIC "一聲長嘯，施出絕招「" HIY "無影掌" HIC
              "」雙掌不斷拍出，掌風作響，劃破長空，將$n" HIC "團團"
              "圍住。\n" NOR;
        message_sort(msg, me, target);
        
        if (random(ap) > dp / 2)
        {
                msg = HIR "$n" HIR "心神懼裂，一時間竟無從應對，"
                      "竟被困在$N" HIR "的掌風之中。\n" NOR;

                target->start_busy(ap / 40 + 1);
                       me->start_busy(1);
                addn("neili", -80, me);
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