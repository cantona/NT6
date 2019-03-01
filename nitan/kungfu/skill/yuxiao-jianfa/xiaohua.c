// xiaohua.c 簫花齊放
// Modified by whuan
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        object weapon;
        int i,j,k,damage;
        if( !target ) target = offensive_target(me);

        if (!objectp(weapon = me->query_temp("weapon")) 
         || (string)weapon->query("skill_type") != "sword")
        if (!objectp(weapon = me->query_temp("secondary_weapon"))
         || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你手中無劍，如何使得玉蕭劍法的精妙絕招？\n");
    
        if( time() < 10+(int)me->query_temp("xiaohua") )        
                return notify_fail("你剛使「簫花齊放」攻敵，氣血洶湧，無法出招！\n");    
    
        if ( (int)me->query("neili") <500)
                return notify_fail("你的內力不夠，無法使出「簫花齊放」！\n");
        
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「簫花齊放」只能對戰鬥中的對手使用。\n");

        if( (int)me->query_skill("yuxiao-jian", 1) < 100 )
                return notify_fail("你的玉簫劍法不夠嫻熟，不會使用「簫花齊放」。\n");

        if( (int)me->query_skill("bibo-shengong", 1) < 100 ) 
                return notify_fail("你的碧波神功修為不夠，無法運用「簫花齊放」攻敵。\n");

        me->set_temp("xiaohua",time());
       
        j=1+me->query_skill("sword")/50; 
        if (j>7) j=7; //計算劍數
        k=(int)me->query_skill("sword");
        damage = k+random(k/2) + me->query_temp("apply/damage");
        damage = damage*11/20;//計算傷害
        
        msg = CYN "$N使出玉簫劍法絕招「簫花齊放」，縱身一躍，連出"+chinese_number(j)+"劍，照向$n。\n";
        message_vision(msg, me, target);

        for (i=0;i<j;i++)
        {
		       if (random(me->query_skill("sword")+target->query_skill("dodge"))>target->query_skill("dodge")) 
		       {
			       message_vision(HIY"\n$n一個不慎，中了一劍！\n"NOR,me,target);
             target->receive_damage("qi",damage,me);
             target->receive_wound("qi",damage/6+random(damage/6),me); 
			       COMBAT_D->report_status(target);
            }
		       else
             message_vision(HIY"\n$n左跳右閃，好不容易才避開了這一劍！\n"NOR,me,target);
         }

        me->start_busy(1+random(2));
        me->add("neili",-30*j);
        return 1;
}
