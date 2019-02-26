//清風拂柳
//edit by gladiator

#include <ansi.h>
#include <combat.h>


#define FULIU HIG "「清風拂柳」" NOR
inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon; 

        if ( !target ) target = offensive_target(me);
        weapon=query_temp("weapon", me);

        if( !userp(me) && me->query_skill("qingliang-jian")<100 && !query("can_perform/qingliang-jian/fuliu", me) )
              return notify_fail("你使用的外功中沒有這種功能！\n");
              
        if ( !target || !target->is_character() || !me->is_fighting(target) )
              return notify_fail(FULIU + "只能對戰鬥中的對手使用。\n");

        if ( (int)me->query_skill("qingliang-jian", 1) < 80 )
              return notify_fail("你的清涼劍法不夠熟練，不能使用" + FULIU + "。\n");

        if ( (int)me->query_skill("force", 1) < 80 
         || (int)me->query_skill("shaolin-xinfa",1 ) < 80)
              return notify_fail("你是否應該在內功修為上多下點功夫。\n");

        if( query("max_neili", me)<1000 )
              return notify_fail("你的內力修為還不夠高。\n");

        if( query("neili", me)<300 )
              return notify_fail("你的內力不夠使用" + FULIU + "。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"
        || me->query_skill_mapped("sword") != "qingliang-jian" )
              return notify_fail("你的劍法不是清涼劍。\n");
        
        if (! living(target)) 
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n"); 
 
        msg = HIG "\n$N暗運真氣，衣袖慢慢鼓了起來，猶似吃飽了風的帆篷一般，"
                  "然而卻又似一陣清風般讓人感到舒服和安逸，\n"
                  "輕輕一劍，就象一陣清風吹落的一片楊柳葉，划向$n。\n" NOR;

        if( random(query("combat_exp", me))>query("combat_exp", target)/3 )
        { 
                me->start_busy(3);
                target->start_busy(random(2));

                damage = (int)me->query_skill("qingliang-jian", 1) + 
                         (int)me->query_skill("dodge", 1) / 2;
                         
                damage = damage /2 + random(damage);
//                target->receive_damage("qi", damage * 2)
//                target->receive_wound("qi", damage)
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, damage / 2,
                        GRN "$n被這招" + FULIU + GRN "輕輕一帶，胸口劃出一條長長的傷口，"
                           "立時鮮血狂噴而出！\n" NOR);
   
                message_vision(msg, me, target);
                COMBAT_D->report_status(target);    
                return 1;
        } else
        {
                me->start_busy(3);
       
                msg += HIG"$n看得分明，連忙提氣縱身，以跳離了$N的劍氣範圍。\n"NOR;
        }
                
        addn("neili", -150, me);
        message_vision(msg, me, target);

        if ( !target->is_fighting(me)) target->fight_ob(me);
        return 1;
}
