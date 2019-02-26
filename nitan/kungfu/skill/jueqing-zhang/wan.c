#include <ansi.h>
#include <combat.h>

#define WAN "「" HIW "萬念俱灰" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/jueqing-zhang/wan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(WAN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(WAN "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("jueqing-zhang", 1) < 100)
                return notify_fail("你絕情掌不夠嫻熟，難以施展" WAN "。\n");

        if (me->query_skill_mapped("strike") != "jueqing-zhang")
                return notify_fail("你沒有激發絕情掌，難以施展" WAN "。\n");

        if (me->query_skill_prepared("strike") != "jueqing-zhang")
                return notify_fail("你沒有準備絕情掌，難以施展" WAN "。\n");

        if (me->query_skill("dodge") < 150)
                return notify_fail("你的輕功修為不夠，難以施展" WAN "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" WAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        ap = me->query_skill("jueqing-zhang", 1) +
             me->query_skill("dodge", 1) / 2;

        dp = target->query_skill("dodge");

        msg = HIC "\n$N" HIC "一聲長嘯，聲音震耳欲聾，悲痛欲絕，頓"
              "感萬念俱灰，猛然間雙掌瘋狂般的拍向$n，看似雜亂無章，"
              "但內中卻隱藏無限殺機。\n" NOR;
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