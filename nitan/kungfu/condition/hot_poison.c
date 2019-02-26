// hot_poison.c
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>;
#include <condition.h>;
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( !living(me) || query_temp("noliving", me) )
        {
                message("vision",me->name()+"全身變黑，散發出一陣焦糊味。\n", environment(me), me);
        }
        else
        {
                tell_object(me,HIR"忽然一股火熱之氣襲來，燙得你手腳亂抖！\n"NOR);
                tell_room(environment(me),HIR+me->name()+"突然全身冒出陣陣紅煙，嘴脣乾裂，雙手胡亂地揮舞着。\n"NOR, ({ me }));
        }
        me->receive_damage("qi", 25,"體內熱毒發作");
        if(userp(me)) me->receive_wound("jing", 20,"體內熱毒發作");
        else me->receive_wound("jing", 40,"體內熱毒發作");
        if(!me->is_busy()) me->start_busy(2);
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("hot_poison", duration - 1);
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}