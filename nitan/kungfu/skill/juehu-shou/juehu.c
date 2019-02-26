// juehu.c 虎爪絕户手「絕户」
// by Lonely

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        int damage, ap, dp;
        string msg, pmsg;
        
        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("神功傷敵只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「絕户」神功！\n");  
                
        if( (int)me->query_skill("juehu-shou", 1) < 100 )
                return notify_fail("你的虎爪絕户手不夠嫻熟，不會使用「絕户」神功\n");

        if( (int)me->query_skill("taiji-shengong", 1) < 100 )
                return notify_fail("你的太極神功不夠高，不能用「絕户」神功傷敵。\n");

        if( query("shen", me)<10000 )
                return notify_fail("你邪氣太重，無法使出「絕户」招式。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在內力太弱，不能使出「絕户」招式。\n");

        msg = BLU "$N默運神功，臉色白得嚇人，突然使出虎爪絕户手的最後一擊「絕户」，企圖當場把$n廢於抓下。\n" NOR;
        
        
        addn("shen", -8000, me);
        me->want_kill(target);
                              
        ap = attack_power(me, "claw"); 
        dp = defense_power(target, "force"); 

        if (ap / 2 + random(ap) > dp) 
        {       
                damage = damage_power(me, "claw");
                addn("neili", -300, me);
                pmsg = RED "結果$N一擊命中，$n只感到下體一陣刺痛，體內精元不斷外泄，頓時覺的四肢無力，兩腿不停顫抖。\n" NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50, pmsg);

                me->start_busy(3);
                target->start_busy(3);                
                
        } else 
        {
                addn("neili", 150, me);
                msg += CYN "可是$p" CYN "看破了$P" CYN "的狠毒企圖，向旁跳開數步，躲開了$P" CYN "的凌厲一擊！\n" NOR;
                me->start_busy(4);
        }
        
        message_combatd(msg, me, target);
        
        if (damage > 200)
        {
                target->apply_condition("juehu_hurt",(500*query("age", target)));
                if( query("gender", target) == "男性" )
                {
                        message_combatd(HIW "$N突然覺的丹田內的精元已流失迨盡，心裏一陣難過，知道自己有一段時間不能行歡做樂了!\n" NOR, target);
                } else
                {
                        if( query("gender", target) == "女性" )
                                message_combatd(HIW "$N被你一擊命中，，不禁既羞又怒，見$n竟對一女流之輩也用此陰毒招數！\n"NOR,
                                                target,me);
                        else
                                message_combatd(HIW "$N雖然擊中$n的要害，但感覺受力甚輕，似乎已無要害可言!\n"NOR,
                                me,target);
                }
          
        }
        
        if (! target->is_killing(me))
                target->kill_ob(me);
        return 1;
}
