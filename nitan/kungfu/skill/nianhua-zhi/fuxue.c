// This program is a part of NITAN MudLIB
// fuxue.c 拈花指 「拈花拂穴」

#include <ansi.h>

inherit F_SSERVER;

string name() { return "拈花拂穴"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("拈花拂穴只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你內功火候不夠，不能使用拈花拂穴！\n");

        if ((int)me->query_skill("finger") < 150)
                return notify_fail("你的指法修為不夠，目前還不能使用拈花拂穴絕技！\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，不能使用拈花拂穴！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if (me->query_skill_mapped("finger") != "nianhua-zhi")
                return notify_fail("你沒有激發拈花指，無法使用拈花拂穴！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "使出拈花指絕技「拈花拂穴」，罩住了$n"
              HIY "的全身，指氣層層疊疊的攻向$p" HIY "的要穴！\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg +=  HIG "結果$p" HIG "被$P" HIG "攻了個措手不及！\n" NOR;
                if (! target->is_busy())
                        target->start_busy(ap/120 + 2);
                addn("neili", -100, me);
                me->start_busy(1);
        }
        else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的招式，連忙躍開，避開了$P"
                       CYN "的攻擊。\n" NOR;
                addn("neili", -30, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
