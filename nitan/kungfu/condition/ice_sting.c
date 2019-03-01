// /kungfu/condition/ice_sting.c
#include <ansi.h>

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( query_temp("nopoison", me))return 0;
        tell_object(me, HIB "你中的" HIC "冰魄銀針毒" HIB "發作了！\n" NOR );
        me->receive_wound("jing", 10,"冰魄銀針毒發作");
        me->receive_damage("qi", 10,"冰魄銀針毒發作");
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("ice_sting", duration - random(5));
        if( duration < 1 ) return 0;
        return 1;
}

string query_type(object me)
{
        return "poison";
}