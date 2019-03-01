// cuff_power.c

#include <condition.h>
#include <ansi.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
                tell_object(me, HIR"你只覺得胸口一股暗勁爆發，哇的吐出一口鮮血！\n" NOR );
        message("vision", HIR"只聽哇~的一聲,"+me->name() + "突然吐出一口鮮血！\n"NOR, environment(me), me);
   
        me->receive_wound("qi",10 + random(duration),"體內拳勁爆發");
        me->receive_wound("jing", 10+ random(duration/5),"體內拳勁爆發");
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("cuff_power", 0);
        return 0;
}

string query_type(object me)
{
        return "hurt";
}