#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "擒龍手" NOR; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手使用。\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("對方沒有使用兵器，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("你內功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你內力修為不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("dragon-strike", 1) < 180)
                return notify_fail("你降龍十八掌火候不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "dragon-strike")
                return notify_fail("你沒有激發降龍十八掌，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "dragon-strike")
                return notify_fail("你沒有準備降龍十八掌，難以施展" + name() + "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "暴喝一聲，全身內勁迸發，氣貫右臂奮力外扯，企圖將$n"
              HIR "的" + weapon->name() + HIR "吸入掌中。\n" NOR;

        ap = attack_power(me, "strike") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_int()*10;

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -300, me);
                msg += HIR "$n" HIR "只覺周圍氣流湧動，手中" + weapon->name()
                       + HIR "竟然拿捏不住，向$N" HIR "掌心脱手飛去。\n" NOR;
                me->start_busy(2);
                weapon->unequip();
                weapon->move(me, 1);
        } else
        {
                addn("neili", -200, me);
                msg += CYN "$n" CYN "只覺周圍氣流湧動，慌忙中連將手中"
                       + weapon->name() + CYN "揮舞得密不透風，使得$N"
                       CYN "無從下手。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}
