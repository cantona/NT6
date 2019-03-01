// This program is a part of NITAN MudLIB
// meng.c 「回夢」

#include <ansi.h>

inherit F_SSERVER;

string name() { return "回夢"; }

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「回夢」只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「回夢」！\n");

        if( (int)me->query_skill("boyun-suowu", 1) < 140 )
                return notify_fail("你的撥雲鎖霧不夠嫻熟，不會使用「回夢」。\n");

        if( (int)me->query_skill("biyun-xinfa", 1) < 130 )
                return notify_fail("你的碧雲心法不夠高，不能用來反震傷敵。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用「回夢」。\n");

        msg = CYN "$N默念口訣，使出「撥雲鎖霧」之「回夢」，意欲以內力震暈$n。\n"NOR;


        ap = attack_power(me, "hand");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                //target->start_busy(random(3));

                damage = damage_power(me, "hand");

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/2);
                addn("neili", -300, me);

                if( damage < 20 )
                        msg += HIY"結果$n受到$N的內力反震，悶哼一聲，看上去很是疲憊。\n"NOR;
                else if( damage < 40 )
                        msg += HIY"結果$n被$N以內力反震，只覺得胸中煩悶，只想好好休息休息。\n"NOR;
                else if( damage < 80 )
                        msg += RED"結果$n被$N以內力一震，腦中嗡嗡作響，意識開始模糊起來！\n"NOR;
                else
                        msg += HIR"結果$n被$N的內力一震，眼前一黑，向後便倒，眼看就要不醒人事了！\n"NOR;

        }
        else
        {
                me->start_busy(3);
                msg += CYN"可是$p看破了$P的企圖，並沒有上當。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
