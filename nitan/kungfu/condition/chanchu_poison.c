// chanchu_poison.c
#include <ansi.h>

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( query_temp("nopoison", me))return 0;
        if( duration < 1 ) return 0;
        if (me->is_ghost())
        {
                me->clear_condition("chanchu_poison");
                return 0;
                }
        me->receive_wound("qi", 25+random(20),"蟾蜍毒發作");
        me->receive_damage("jing", 15+random(20),"蟾蜍毒發作");
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("chanchu_poison", duration - 1);
        tell_object(me, HIG"你覺得傷口一陣陣發涼，沒啥感覺了。你中的蟾蜍毒發作了！\n" NOR );
        return 1;
}

string query_type(object me)
{
        return "poison";
}