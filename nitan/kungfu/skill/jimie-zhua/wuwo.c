// jue.c 絕命抓 

#include <ansi.h> 
#include <combat.h> 

inherit F_SSERVER; 

int perform(object me) 
{ 
        string msg; 
        object target; 
        int skill, ap, dp, damage; 

        if (! target) 
        {
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }

        if (! target || ! me->is_fighting(target)) 
                return notify_fail("「眾生無我」只能在戰鬥中對對手使用。\n"); 

         skill = me->query_skill("jimie-zhua", 1); 

        if( userp(me) && me->query_skill("jimie-zhua",1)<120 && !query("can_perform/jimie-zhua/wuwo", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");  

         if (skill < 100) 
                return notify_fail("你的寂滅抓等級不夠，不會使用「眾生無我」！\n"); 

         if( query("neili", me)<250 )
                return notify_fail("你的真氣不夠！\n"); 

         if (me->query_skill_mapped("claw") != "jimie-zhua")  
                return notify_fail("你沒有激發寂滅抓，無法使用「眾生無我」！\n"); 

         if (! living(target)) 
                 return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n"); 
         msg = HIY "$N" HIY "猛地撲上前來，雙抓分兩路$n" HIY "抓出，平淡" 
               "的一擊，卻顯示出紮實的基本功！\n" NOR; 

         ap = me->query_skill("force") + me->query_skill("claw"); 
         dp = target->query_skill("parry") + target->query_skill("dodge"); 
         if (ap / 2 + random(ap) > dp) 
         { 
                 addn("neili", -200, me);
                 damage = ap / 3 + random(ap / 4); 
                 msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55, 
                                            HIR "慌亂中，$p" HIR "不及招架$P這看似" 
                                            HIR "簡單這一抓，結果被抓了個正中，" 
                                            "喀的一聲，$p身上多了一條傷痕。\n" NOR); 
                 me->start_busy(2); 
         } else 
         { 
                 msg += CYN "可是$p" CYN "$P見來勢兇猛" CYN 
                        "連忙招架，順勢躍開，沒有被$P" 
                        CYN "得手。\n" NOR; 
                  addn("neili", -20, me);
                  me->start_busy(3); 
          } 
          message_combatd(msg, me, target); 

           return 1; 
}
