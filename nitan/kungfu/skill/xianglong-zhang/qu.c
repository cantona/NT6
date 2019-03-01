#include <ansi.h>
inherit F_SSERVER;

#define QU "「" HIW "雙龍取水" NOR "」"

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;

        if( userp(me) && !query("can_perform/xianglong-zhang/qu", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(QU "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(QU "只能空手使用。\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 150)
                return notify_fail("你降龍十八掌火候不夠，難以施展" QU "。\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("你沒有激發降龍十八掌，難以施展" QU "。\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("你沒有準備降龍十八掌，難以施展" QU "。\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("對方沒有使用兵器，難以施展" QU "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠，難以施展" QU "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不夠，難以施展" QU "。\n");

        if( query("neili", me)<500 )
                return notify_fail("你現在的真氣不足，難以施展" QU "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "暴喝一聲，全身內勁迸發，氣貫右臂奮力外扯，企圖將$n"
              HIW "的" + weapon->name() + HIW "吸入掌中。\n" NOR;

        ap=me->query_skill("strike")+query("str", me)*10;
        dp=target->query_skill("parry")+query("dex", target)*10;

        if (ap / 3 + random(ap) > dp)
        {
                addn("neili", -300, me);
                msg += HIR "$n" HIR "只覺周圍氣流湧動，手中" + weapon->name()
                       + HIR "竟然拿捏不住，向$N" HIR "掌心脫手飛去。\n" NOR;
                me->start_busy(2);
                weapon->move(me, 1);
        } else
        {
                addn("neili", -200, me);
                msg += CYN "$n" CYN "只覺周圍氣流湧動，慌忙中連將手中"
                       + weapon->name() + CYN "揮舞得密不透風，使得$N"
                       CYN "無從下手。\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);
        return 1;
}