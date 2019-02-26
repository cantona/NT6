// warn_poison 硃砂掌毒
// Last Modified by winder on Aug. 25 2001

#include <ansi.h>;
#include <condition.h>;
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( !living(me) || query_temp("noliving", me) )
        {
                message("vision", me->name()+"喘着粗氣，面色赤紅。\n", environment(me), me);
        }
        else
        {
                tell_object(me, RED"你只覺渾身燥熱難耐，似乎被放在火爐中一樣，極為難受！\n" NOR );
                message("vision", RED+me->name()+"突然面色一紅，渾身一抖，自頭部到手臂隱約可見斑斑紅點，極為恐怖。\n"NOR, environment(me), me);
        }
        me->receive_damage("qi", 25,"硃砂掌毒發作");
        me->receive_wound("jing", 20,"硃砂掌毒發作");
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("warm_poison", duration - 1);
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}
