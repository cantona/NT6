// zhen.c 猴拳「震」字訣
// by Lonely

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
int perform(object me, object target)
{
        int damage;
        string msg, pmsg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("神功震敵只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「震」字訣！\n");         
                
        if( (int)me->query_skill("mizong-houquan", 1) < 40 )
                return notify_fail("你的猴拳不夠嫻熟，不會使用「震」字訣。\n");
                                
        if( query("neili", me)<200 )
                return notify_fail("你現在內力太弱，不能使用「震」字訣。\n");
                        
        msg = CYN "$N默運神功，使出猴拳「震」字訣，企圖以內力震傷$n。\n"NOR;

        if (random(me->query_skill("force")) > target->query_skill("force") / 2 )
        {       
                damage = (int)me->query_skill("force", 1);
                
                damage = 100 + random(damage/2);
                addn("neili", -200, me);
                
                if( damage < 20 ) pmsg = HIY"結果$n受到$N的內力反震，悶哼一聲。\n"NOR;
                else if( damage < 40 ) pmsg = HIY"結果$n被$N以內力反震，「嘿」地一聲退了兩步。\n"NOR;
                else if( damage < 80 ) pmsg = RED"結果$n被$N以內力一震，胸口有如受到一記重錘，連退了五六步！\n"NOR;
                else pmsg += HIR"結果$n被$N的內力一震，眼前一黑，身子向後飛出丈許！！\n"NOR;
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30, pmsg);
                
                me->start_busy(3);
                if (! target->is_busy())
                        target->start_busy(random(3));
                
        } else 
        {
                addn("neili", -50, me);
                me->start_busy(3);
                msg += CYN"可是$p看破了$P的企圖，並沒有上當。\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
