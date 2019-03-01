//gladiator

#include <ansi.h>
#include <combat.h> 

inherit F_SSERVER;

void remove_effect(object me, int improve);

int perform(object me, object target)
{
        int lev, lev2;
        string msg;
        
        lev = (int)me->query_skill("mohe-zhi", 1)/4;
        lev2 = (int)me->query_skill("finger", 1)/4;
    
        if( userp(me) && !query("can_perform/mohe-zhi/mohe", me) )
                return notify_fail("你所使用的外功中沒有這樣的功能。\n");
                    
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「摩訶參禪」只能在戰鬥中使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你拿著武器怎麼能使用「摩訶參禪」！\n");   

        if( (int)me->query_skill("mohe-zhi", 1) < 80 )
                return notify_fail("你的摩訶指還不夠嫻熟，使不出「摩訶參禪」絕技。\n");

        if((int)me->query_skill("force") < 80 ) 
                return notify_fail("你的內功修為還不夠，使不出「摩訶參禪」絕技。\n");

        if ( me->query_skill_mapped("finger") != "mohe-zhi" )
                return notify_fail("你現在無法使用「摩訶參禪」！\n"); 

        if( query("max_neili", me)<(me->query_skill("force")+1000) )
                return notify_fail("你現在內力太弱，使不出「摩訶參禪」。\n");      

        if( query("neili", me)<800 )
                return notify_fail("你現在真氣太弱，使不出「摩訶參禪」。\n");

        msg = HIY "\n$N不動聲色，衣袖輕擺，幾縷指風無聲無息彈出。\n" NOR;
        message_vision(msg, me, target); 
        
        addn_temp("apply/finger", lev, me);
        addn_temp("apply/attack", lev2, me);
        
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);

        if( random(query("combat_exp", me))>query("combat_exp", target)/2 )
        {    
               COMBAT_D->do_attack(me,target,query_temp("weapon", me),2);
               
        } else
        {
               COMBAT_D->do_attack(me,target,query_temp("weapon", me),1);
        }
        addn_temp("apply/finger", -lev, me);
        addn_temp("apply/attack", -lev2, me);
        addn("neili", -350, me);
        addn("jingli", -50, me);
        me->start_busy(1 + random(2));
        target->start_busy(1);
        return 1;
}
