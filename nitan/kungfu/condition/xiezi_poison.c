// xiezi_poison.c
#include <ansi.h>

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( query_temp("nopoison", me))return 0;
        if( duration < 1 ) return 0;
        me->receive_wound("qi", 15+random(10), "蠍子毒發作");
        me->receive_damage("jing", 25+random(20), "蠍子毒發作");
        tell_object(me, HIG"你感到呼吸困難，四肢漸漸腫了起來。你中的蠍子毒發作了！\n" NOR );
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("xiezi_poison", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "poison";
}