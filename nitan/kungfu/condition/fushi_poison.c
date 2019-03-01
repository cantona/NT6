// Last Modified by winder on May. 15 2001
// fushi_poison.c 府屍毒

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
int update_condition(object me, int duration)
{         
  if (me->is_ghost()) return 1;
        tell_object(me,HIB"你突然覺得一股惡臭從腹中升起，不禁大嘔起來！\n"NOR);
        tell_room(environment(me),HIB + me->name()+"臉上浮著一層黑氣，腳步蹣跚，突然吐出一堆穢物！\n" NOR, ({ me }));             
        me->receive_wound("jing", 25,"腐屍毒發作");
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("fushi_poison", duration - 1);   
        if( duration < 1 ) return 0;   
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}