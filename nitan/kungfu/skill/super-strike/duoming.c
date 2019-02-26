// by darken@SJ

#include <ansi.h>
#include <combat.h> 
inherit F_SSERVER;

string perform_name(){ return HBBLU"奪命鐵爪"NOR; }
int perform(object me, object target)
{
        int skill;
        skill = (int)me->query_skill("super-strike", 1);
        if( !target ) target = offensive_target(me);

        if( !target || !me->is_fighting(target) )
                return notify_fail("「奪命鐵爪」只能在戰鬥中使用。\n");
        if( me->query_temp("weapon"))
                return notify_fail("你拿着武器怎麼能使用「奪命鐵爪」！\n");   
   if(me->query_skill("force",1) < 200 )
                return notify_fail("你的歸元吐吶法不夠嫻熟，使不出「奪命鐵爪」。\n");
        if(me->query_skill_mapped("strike") != "super-strike" )
               return notify_fail("你現在無法使用「奪命鐵爪」！\n");
        if( (int)me->query("max_neili") < 3000)
                return notify_fail("你現在內力太弱，使不出「奪命鐵爪」。\n");      
        if( (int)me->query("neili") < 2500 )
                return notify_fail("你現在真氣太弱，使不出「奪命鐵爪」。\n");
      
        message_vision(HBBLU"\n$N左掌拍出，右手成抓，同時襲到，兩股強力排山倒海般壓向$n！\n"NOR,me,target);
        if (random(me->query_dex()) > target->query_dex()/3) {
           message_vision(HIR"結果$n被$N右手牢牢抓住！\n"NOR,me,target);
           if(!target->is_busy()) target->start_busy(2);
        }
        message_vision(HBBLU"\n$N左掌一掌掌的拍向$n！\n"NOR,me,target);
        me->add("neili", -800-random(200));
        if(me->is_fighting(target)) 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        if(me->is_fighting(target)) 
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
        me->start_perform(6,"「奪命鐵爪」");
        return 1;
}

