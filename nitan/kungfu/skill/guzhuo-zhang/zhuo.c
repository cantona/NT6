#include <ansi.h>
#include <combat.h>

#define ZHUO "「" WHT "大巧若拙" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/guzhuo-zhang/zhuo", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUO "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(ZHUO "只能空手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("force") < 220)
                return notify_fail("你內功修為不夠，難以施展" ZHUO "。\n");

        if( query("max_neili", me)<1800 )
                return notify_fail("你內力修為不夠，難以施展" ZHUO "。\n");

        if ((int)me->query_skill("guzhuo-zhang", 1) < 150)
                return notify_fail("你古拙掌法火候不夠，難以施展" ZHUO "。\n");

        if (me->query_skill_mapped("strike") != "guzhuo-zhang")
                return notify_fail("你沒有激發古拙掌法，難以施展" ZHUO "。\n");

        if (me->query_skill_prepared("strike") != "guzhuo-zhang")
                return notify_fail("你沒有準備古拙掌法，難以施展" ZHUO "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，難以施展" ZHUO "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "手腕一探，平平推出一掌，頓時掌風激進，塵沙四起，直"
              "刮得$n" WHT "面龐隱隱生疼。\n" NOR;
        addn("neili", -150, me);

        ap = me->query_skill("strike");
        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)

        {
                msg += HIR "$n" HIR "見$N" HIR "掌風凌厲，慌"
                       "忙招架，頓時便失了先機。\n" NOR;
                target->start_busy((int)me->query_skill("guzhuo-zhang", 1) / 22 + 2);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$n" CYN "不慌不忙，看破了$N"
                       CYN "此招虛實，並沒有受到半點影響。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}