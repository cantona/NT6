// cold_poison.c
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>;
#include <condition.h>;
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( !living(me) || query_temp("noliving", me) )
        {
                message("vision", HIW+me->name()+"瑟瑟發抖，全身結上一層薄薄的白霜。\n"NOR, environment(me), me);
        }
        else {
                tell_object(me, HIW"忽然一股寒氣優似冰箭，循著手臂，迅速無倫的射入胸膛，你中的寒毒發作了！\n"NOR);
                message("vision", HIW+me->name()+"全身發顫，牙關格格直響，過得片刻，嘴唇也紫了，臉色漸漸由青而白。\n"NOR, environment(me), me);
        }
        me->receive_damage("qi", 35,"體內寒毒發作");
        if(userp(me)) me->receive_wound("jing", 20,"體內寒毒發作");
        else me->receive_wound("jing", 40,"體內寒毒發作");
        if(!me->is_busy()) me->start_busy(2);
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("cold_poison", duration - 1);
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}