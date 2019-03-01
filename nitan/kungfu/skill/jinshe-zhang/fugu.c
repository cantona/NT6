// This program is a part of NITAN MudLIB
// fugu.c 金蛇遊身掌-附骨纏身

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("附骨纏身只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你不是空手，不能使用附骨纏身。\n");

        if ((int)me->query_skill("jinshe-zhang", 1) < 100)
                return notify_fail("你的金蛇掌不夠嫻熟，不會使用附骨纏身。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用附骨纏身。\n");

        if (me->query_skill_prepared("strike") != "jinshe-zhang")
                return notify_fail("你現在沒有準備金蛇掌法，無法使用附骨纏身。\n");

        msg = HIC "$N" HIC "大喝一聲，纏身而上左手一探刁住$n"
              HIC "手腕，右掌猛下殺手！\n"NOR;
        message_combatd(msg, me, target);

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");
             
        if (target->is_busy() ||
            (ap / 2 + random(ap)) > dp)
        {
                if (! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
                COMBAT_D->do_attack(me, target, 0, 0);
                COMBAT_D->do_attack(me, target, 0, 0);

                addn("neili", -150, me);
                me->start_busy(2);
                msg = HIR "結果$n" HIR "被$N" HIR "的左手所制，"
                      "在「附骨纏身」下，一時竟然無法還手！\n" NOR;
        }
        else
        {
                me->start_busy(2);
                msg = CYN "可是$p" CYN "識破了$P"
                      CYN "這一招，手肘一送，擺脫了對方控制。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
