// This program is a part of NITAN MudLIB
// gu.c 孤注一擲

#include <ansi.h>

inherit F_SSERVER;

string name() { return "孤注一擲"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「孤注一擲」只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「孤注一擲」！\n");

        if( (int)me->query_skill("cuixin-zhang", 1) < 60 )
                return notify_fail("你的催心掌不夠嫻熟，不會使用「孤注一擲」!\n");

        if (me->query_skill_mapped("strike") != "cuixin-zhang")
                return notify_fail("你沒有準備使用催心掌，無法施展「"RED"孤注一擲"CYN"」。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用「孤注一擲」!\n");

        msg = CYN "$N默運神功，使出「"RED"孤注一擲"CYN"」，雙掌平推攻向$n。\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                me->start_busy(random(2));
                if (! target->is_busy())
                        target->start_busy(random(3));

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);
                addn("neili", -damage/3, me);

                if( damage < 40 )
                        msg += HIY"結果$n被$N雙掌打在胸口，悶哼一聲。\n"NOR;
                else if( damage < 80 )
                        msg += HIY"結果$n被$N以雙掌打在胸口，「嘿」地一聲退了兩步。\n"NOR;
                else if( damage < 160 )
                        msg += RED"結果$n被$N以雙掌打在胸口，有如受到一記重錘，連退了五六步！\n"NOR;
                else
                        msg += HIR"結果$n被$N的雙掌打在胸口，眼前一黑，象一捆稻草一樣飛出去好幾丈遠！\n"NOR;

        }
        else
        {
                me->start_busy(1 + random(2));
                msg += CYN"可是$p看破了$P的企圖，身形一轉，反掌回擊。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
