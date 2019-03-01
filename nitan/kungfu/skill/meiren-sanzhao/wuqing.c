// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "玉女無情"; }

int perform(object me, object target)
{
        string msg;
        int damage, ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("玉女無情只能對戰鬥中的對手使用。\n");

        if( (int)me->query_skill("unarmed", 1) < 120 )
                return notify_fail("你的基本掌法級別不夠，不會使用玉女無情。\n");

        if (me->query_skill_mapped("strike") != "meiren-sanzhao")
                return notify_fail("你沒有激發美人三招，難以施展「玉女無情」。\n");

        if (me->query_skill_prepared("strike") != "meiren-sanzhao")
                return notify_fail("你沒有準備美人三招，難以施展「玉女無情」。\n");

        if( (int)me->query_skill("force", 1) < 120 )
                return notify_fail("你的內功還未嫻熟，不能用玉女無情。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在內力太弱，不能使用玉女無情。\n");

        msg = HIB "\n\n$N真氣催動，帶得劍意縱橫無情！\n" NOR;
        msg += HIY "\n$N右手支頤，左袖輕輕揮出，長嘆一聲，臉現寂寥之意，無奈中使出殺招。\n\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -300, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "只聽砰、砰、砰三聲巨響，$n面如紙色，鮮血狂噴。\n" NOR);
                me->start_busy(2+random(2));
        }
        else
        {
                msg += HIG"$p靈光一現，縱身躍起，本能的反應幫$p逃過此劫。\n\n"NOR;
                addn("neili", -100, me);
                me->start_busy(2);
        }

        message_combatd(msg, me, target);
        return 1;
}

