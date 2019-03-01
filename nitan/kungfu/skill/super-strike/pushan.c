// by darken@SJ
#include <ansi.h>
#include <combat.h>

 inherit F_SSERVER;
 string perform_name(){ return HBBLU"鐵蒲扇掌"NOR; }
 int perform(object me, object target)
 {
         int j;
         string msg;
         j = me->query_skill("super-strike", 1);

         if( !target ) target = offensive_target(me);

         if( !target 
           || !me->is_fighting(target)
           || !living(target)
           || environment(target)!= environment(me))
                 return notify_fail("「鐵蒲扇掌」只能在戰鬥中對對手使用。\n");

         if( objectp(me->query_temp("weapon")) )
                 return notify_fail("你必須空手才能使用「鐵蒲扇掌」！\n");

         if( (int)me->query_skill("super-strike", 1) < 250 )
                 return notify_fail("你的鐵掌不夠嫻熟，使不出「鐵蒲扇掌」絕技。\n");

         if( (int)me->query_skill("force", 1) < 250 )
                 return notify_fail("你歸元吐納法不夠，使不出「鐵蒲扇掌」絕技。\n");

         if( (int)me->query("jiali") < 120 )
                 return notify_fail("你加力不夠，使不出「鐵蒲扇掌」絕技。\n");

         if( (int)me->query_skill("force") < 250 )
                 return notify_fail("你的內功等級不夠，不能使用「鐵蒲扇掌」。\n");

         if( (int)me->query_str() < 40 )
                 return notify_fail("你的膂力還不夠強勁，使不出「鐵蒲扇掌」來。\n");

         if (me->query_skill_prepared("strike") != "super-strike"
          || me->query_skill_mapped("strike") != "super-strike"
          || me->query_skill_mapped("parry") != "super-strike")
                 return notify_fail("你現在無法使用「鐵蒲扇掌」！\n");

         if( (int)me->query("max_neili") < 2000)
                 return notify_fail("你現在內力太弱，使不出「鐵蒲扇掌」。\n");

         if( (int)me->query("neili") < 1500 )
                 return notify_fail("你現在真氣太弱，使不出「鐵蒲扇掌」。\n");
         
         if( target->query_temp("pushan") )
                 return notify_fail("別那麼殘忍啦。\n");

         msg = HIW "\n$N你深吸一口氣，大喝一聲，施出鐵掌掌法中的“鐵蒲扇掌”擊向$n！\n"NOR;
          if ( target->query_con()/3 < random(me->query_con())) {
              msg += HIG"\n$n雙掌一並，硬是接下了$N這一掌！\n"NOR;
              if (target->query_str() < me->query_str()) {
                  target->add_temp("apply/strength",-me->query_str());
                  target->set_temp("pushan",me->query_str());
                  target->receive_wound("qi",j*4);
                  target->receive_damage("qi",j*8);
                  msg += HIR"\n只聽見喀啦一聲，$n的腕骨居然被硬生生的震斷了！\n"NOR;
                  
              } else {
                  msg += HIR"\n$n哇地噴出一口鮮血，似乎受了極重的內傷！\n"NOR;
                 
                  target->receive_wound("qi",j*3);
                  target->receive_damage("qi",j*6);
              }
              message_vision(msg, me, target);
              COMBAT_D->report_status(target);
         } else {
             msg += HIY"\n$n見來勢兇猛，不敢硬擋，連忙轉身避開！\n"NOR;
             msg += HIR"\n豈知$N已經埋伏下厲害後著，連出兩掌重手！\n"NOR;
                 message_vision(msg, me, target);
             me->set_temp("tzzf",1);
                 if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             if(objectp(target)
             && me->is_fighting(target))
                     COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 3);
             me->delete_temp("tzzf");
         }               

         me->add("neili", -1500);
         me->start_busy(random(2));
         
         me->start_perform(5,"「鐵蒲扇掌」");
         return 1;
 }

