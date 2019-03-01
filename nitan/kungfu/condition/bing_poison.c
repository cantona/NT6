// bing_poison.c
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>;
#include <condition.h>;
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        tell_object(me,HIB"突然你感覺四肢麻麻的似乎不大靈便！\n"NOR);
        tell_room(environment(me),HIB+me->name()+"突然全身一顫，兩張手掌心已全成黑色，黑氣更順着手臂向上攀升！\n"NOR, ({ me }));     
        me->receive_damage("qi", 25);
        if(userp(me)) me->receive_wound("jing", 20,"中冰晶毒");
        else me->receive_wound("jing", 40,"中冰晶毒");
        if(!me->is_busy()) me->start_busy(2);
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("bing_poison", duration - 1);
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}