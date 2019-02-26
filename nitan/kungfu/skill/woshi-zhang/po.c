// po.c 

#include <ansi.h> 
#include <combat.h>  

inherit F_SSERVER;  

int perform(object me, object target)  
{
        string msg;  
        int damage;  

        if (! target) target = offensive_target(me);  

        if (! target || ! me->is_fighting(target))  
                return notify_fail("「碎石破玉」只能在戰鬥中對對手使用。\n");  

        if( userp(me) && !query("can_perform/woshi-zhang/po", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");  

        if( query_temp("weapon", me) || 
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手才能使用「碎石破玉」！\n");  

        if (me->query_skill("force") < 140)  
                return notify_fail("你的內功的修為不夠，不能使用這一絕技！\n");  

        if (me->query_skill("woshi-zhang", 1) < 120)  
                return notify_fail("你的握石掌修為不夠，目前不能使用「碎石破玉」！\n");  

        if (me->query_skill_mapped("strike") != "woshi-zhang") 
                return notify_fail("你沒有激發握石掌，難以施展「碎石破玉」。\n"); 

        if( query("neili", me)<400 )
                return notify_fail("你現在真氣不夠，難以施展「碎石破玉」。\n"); 

        if (! living(target)) 
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n"); 

        msg = HIW "只見$N" HIW "聚力於掌，猛然間怒喝一聲，一掌破空而至，正是" 
              "握石掌的一招「開碑碎石」，破空劈向$n" HIW "而去！\n" NOR; 

        if (random(me->query_skill("strike")) > target->query_skill("parry") / 2) 
        { 
                me->start_busy(3); 

                damage = me->query_skill("woshi-zhang", 1); 
                damage = damage * 2 + random(damage * 5); 
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35, 
                                           HIR "結果只聽$n" HIR "一聲慘嚎，胸口" 
                                           HIR "以被$N掌勁結結實實的轟中，“哇”的噴出一大" 
                                           "口鮮血。\n" NOR); 
                addn("neili", -250, me);
        } else 
        {
                me->start_busy(2); 
                addn("neili", -120, me);
                msg += CYN "可是$p" CYN "看破了$N" CYN 
                       "的企圖，躲開了這招殺着。\n" NOR; 
        }
        message_combatd(msg, me, target); 

        return 1; 
}
