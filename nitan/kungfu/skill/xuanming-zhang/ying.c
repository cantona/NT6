#include <ansi.h>
#include <combat.h>

#define YING "「" HIW "如影相隨" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/xuanming-zhang/ying", me) )
                return notify_fail("你還沒有經過人指點，不會使用"YING"。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YING "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(YING "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 100)
                return notify_fail("你玄冥神掌不夠嫻熟，難以施展" YING "。\n");

        if (me->query_skill_mapped("strike") != "xuanming-zhang")
                return notify_fail("你沒有激發玄冥神掌，難以施展" YING "。\n");

        if (me->query_skill_prepared("strike") != "xuanming-zhang")
                return notify_fail("你沒有準備玄冥神掌，難以施展" YING "。\n");

        if (me->query_skill("dodge") < 180)
                return notify_fail("你的輕功修為不夠，難以施展" YING "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" YING "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        msg = HIC "\n$N" HIC "長嘯一聲，施出絕招「" HIW "如影相隨" HIC "」，"
              "雙掌不斷翻騰，掌風中透出陣陣陰寒之氣，將$n" HIC "籠罩。\n" NOR;
        message_sort(msg, me, target);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = HIR "$n" HIR "頓覺寒氣避人，一時間無從應對，"
                      "竟被困在$N" HIR "的掌風之中。\n" NOR;

                target->start_busy(1 + ap / 80);
                me->start_busy(1);
                addn("neili", -180, me);
        } else
        {
                msg = CYN "$n" CYN "看破$N" CYN "毫無攻擊之意，于"
                      "是大膽反攻，將$N" CYN "這招盡數化解。\n" NOR;

                me->start_busy(2);
                addn("neili", -100, me);
        }
        message_vision(msg, me, target);

        return 1;
}
