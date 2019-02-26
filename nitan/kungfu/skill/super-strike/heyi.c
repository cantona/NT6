// 鐵掌掌法 -- 陰陽合一
// Modified by snowman@SJ 19/12/2000

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string perform_name(){ return HBBLU"陰陽合一"NOR; }
int perform(object me, object target)
{
        int j;

        if( !target ) target = offensive_target(me);

        if( !target 
          || !me->is_fighting(target)
          || !living(target)
          || environment(target)!= environment(me))
                return notify_fail("「陰陽合一」只能在戰鬥中對對手使用。\n");

        if( me->query_temp("weapon") )
                return notify_fail("你必須空手才能使用「陰陽合一」！\n");

        if( (int)me->query_skill("super-strike", 1) < 200 )
                return notify_fail("你的鐵掌掌法還不夠嫻熟，使不出「陰陽合一」絕技。\n");

        if( (int)me->query_skill("force", 1) < 200 )
                return notify_fail("你的歸元吐納法等級不夠，使不出「陰陽合一」絕技。\n");

        if( (int)me->query_skill("force") < 230 )
                return notify_fail("你的內功等級不夠，不能使用「陰陽合一」。\n");

        if( (int)me->query_str() < 33 )
                return notify_fail("你的膂力還不夠強勁，使不出「陰陽合一」來。\n");

        if (me->query_skill_prepared("strike") != "super-strike"
         || me->query_skill_mapped("strike") != "super-strike"
         || me->query_skill_mapped("parry") != "super-strike")
                return notify_fail("你現在無法使用「陰陽合一」！\n");    
        
        if( (int)me->query("max_neili") < 1500)
                return notify_fail("你現在內力太弱，使不出「陰陽合一」。\n");      

        if( (int)me->query("neili") < 1000 )
                return notify_fail("你現在真氣太弱，使不出「陰陽合一」。\n");

        if((int)me->query_temp("tzzf") && userp(me)) 
                return notify_fail("你正在使用掌刀。\n");

	j = me->query_skill("super-strike", 1)/3;
        message_vision(HIW"\n$N退了兩步，突然身子微側，緊跟着身形猛進直擊$n！\n"NOR, me, target);

        me->add_temp("apply/strike", j);
        me->add_temp("apply/damage", j/2);
        me->add_temp("apply/attack", j);
        me->set_temp("tz/heyi", 1);
        COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 1);
        me->set_temp("tz/heyi", 2);
        if(me->is_fighting(target)){
          	if(random(me->query("combat_exp",1)) > target->query("combat_exp", 1)/3)
            		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
          	else
            		COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
        }
        me->delete_temp("tz/heyi");
        me->add_temp("apply/strike", -j);
        me->add_temp("apply/damage", -j/2);
        me->add_temp("apply/attack", -j);
        if( j * 4 > 250 && random(2) ){
        	tell_object(me, HIY"\n緊接着你掌勢一變，開始凝聚祕傳的“天雷氣”……\n"NOR);
        	me->start_call_out( (: call_other, __DIR__"tianlei", "tianlei_hit", me, 2 :), 1 );
        }
        me->add("neili", -500);
        me->add("jingli", -100);
        me->start_perform(5,"「陰陽合一」");
        return 1;
}

int help(object me)
{
        write(WHT"\n鐵掌掌法「陰陽合一」："NOR"\n");
        write(@HELP
        這是裘千仞鐵掌功的十三絕招之一，叫作「陰陽合一」，最是猛惡無比。
        而且據幫中護法説，還看過幫主在此招之後出過一式殺招！
        
        要求：  內力 1000 以上；      
                最大內力 1500 以上；
                精力 100 以上；  
                後天膂力 33 以上；
                鐵掌掌法等級 140 以上；
                歸元吐納法等級 140 以上；    
                且手無兵器。
HELP
        );
        return 1;
}
