// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "仙遊訣" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, level;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"只有在戰鬥中才能使用。\n");

        if ((level = me->query_skill("xiaoyaoyou", 1)) < 100)
                return notify_fail("你的逍遙遊掌法不夠熟練，難以施展"+name()+"。\n");

        if (me->query_skill_mapped("dodge") != "xiaoyaoyou")
                return notify_fail("你沒有激發逍遙遊為輕功，難以施展"+name()+"。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不足，難以施展"+name()+"。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "身子微晃，施出「" HIG "仙遊訣"
              HIW "」滿場遊走，步法洋洋灑灑，甚為飄逸。\n" NOR;

        ap = attack_power(me, "dodge");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "只見無數人影奔來，不由大"
                       "驚失色，攻勢頓為緩滯。\n" NOR;
                target->start_busy(level / 80 + 2);
                me->start_busy(1);
                addn("neili", -80, me);
        } else
        {
                msg += CYN "可是$n" CYN "看破了$P" CYN "的身"
                       "法，並沒有受到任何影響。\n" NOR;
                me->start_busy(2);
                addn("neili", -50, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
