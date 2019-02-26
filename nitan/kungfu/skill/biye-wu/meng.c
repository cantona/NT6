// This program is a part of NITAN MudLIB
// meng.c 碧葉隨風舞「迴夢」

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;        

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「迴夢」只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「迴夢」！\n");           

        if( (int)me->query_skill("biye-wu", 1) < 40 )
                return notify_fail("你的碧葉隨風舞不夠嫻熟，不會使用「迴夢」。\n");

        if( (int)me->query_skill("biyun-xinfa", 1) < 30 )
                return notify_fail("你的碧雲心法不夠高，不能用來反震傷敵。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用「迴夢」。\n");

        msg = CYN "$N默唸口訣，使出碧葉隨風舞之「迴夢」，意欲以內力震暈$n。\n"NOR;

        
        ap = attack_power(me, "force");
        dp = defense_power(target, "force");
        
        if (ap / 2 + random(ap) > dp)
        {
                //me->start_busy(3);
                //target->start_busy(random(3));
                
                damage = damage_power(me, "force");
                
                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/6);
                addn("neili", -damage/3, me);
                
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
                me->start_busy(4);
                msg += CYN"可是$p看破了$P的企圖，並沒有上當。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
