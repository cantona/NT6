// Code of ShenZhou
//rama@sz modified from xx_poison
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
//      int ml;
//      ml = me->query("max_neili")/1000;
        if (duration < 1) return 0;
   if( !living(me) ) {
      message("vision", me->name() + "痛苦地哼了一聲。\n", environment(me), me);
   }
   else {
      tell_object(me, HIB "忽然一陣刺骨的奇寒襲來，你中的冰蠶劇毒發作了！\n" NOR );
      message("vision", me->name() + "的身子突然晃了兩晃，牙關格格地響了起來。\n",
            environment(me), me);
   }
   if( objectp(query("poisoner", me))){
      me->receive_wound("qi",random(duration)/2+10,query("poisoner", me));
      me->receive_wound("jing",random(duration)/2+10,query("poisoner", me));
        }
        else{
      me->receive_wound("qi", random(duration)/2+10);
      me->receive_wound("jing", random(duration)/2+10);
        }

        if( query("qi", me)<1 || query("jing", me)<1 )
        {
                set_temp("die_reason", "冰蠶劇毒攻心死了", me);
                me->die();
                return 0;
        }


//   if(!userp(me)) me->receive_curing("jing", 12);

      me->apply_condition("bingcan_poison", duration - 1);
//    me->apply_condition("xx_poison", duration - 1); 
        
   if( duration == 1)delete("poisoner", me);

   if( duration < 1 ) return 0;
   return CND_CONTINUE;
}

