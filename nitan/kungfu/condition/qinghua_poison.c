// Last Modified by winder on May. 15 2001
// qinghua_poison.c 情花毒
#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        tell_object(me, HIM"你的手指上刺損處突然劇痛，傷口微細，痛楚竟然厲害之極，宛如胸\n口驀地給人用大鐵錘猛擊一下，你忍不住「啊」的一聲叫了出來，忙\n將手指放在口中吮吸。\n" NOR );
        tell_room(environment(me), MAG+ me->name()+"全身猶似為千萬只黃蜂同時螯咬，四肢百骸，劇痛難當，忍不住大聲號叫。\n" NOR, ({ me }));
        me->receive_damage("qi", 15,"中情花毒");
        me->receive_wound("jing", 15,"中情花毒");
        if(!me->is_busy()) me->start_busy(2); 
                me->apply_condition("qinghua_poison", duration - 1);
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}