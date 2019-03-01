// This program is a part of NITAN MudLIB
// rou.c 柔字訣

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "柔字訣" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("「柔字訣」只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你要施展拳法不能使用武器。\n");

        if ((int)me->query_skill("lingshe-quan", 1) < 120)
                return notify_fail("你的靈蛇拳法不夠嫻熟，現在還無法使用「柔字訣」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，無法運用「柔字訣」。\n");

        msg = HIG "$N" HIG "一拳打出，半途中手臂忽然不可思議的轉了個圈子，打向$n"
              HIG "，令$p" HIG "防不勝防。\n"NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                if (!target->is_busy())
                        target->start_busy(1);
                damage = damage_power(me, "cuff");

                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "只見$n" HIR "大吃一驚，倉皇之下不及閃躲，被$N"
                                           HIR "一拳打了個正中，悶哼一聲，連退數步！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "見機的快，連忙施展身法，避開了拳。\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}