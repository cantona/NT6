// anqi_poison.c

#include <ansi.h>
#include <condition.h>
inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
  if (me->is_ghost()) return 1;
        if( duration < 1 ) return 0;
        if( !living(me) || query_temp("noliving", me) )
        {
                message("vision", me->name() + "痛苦地哼了一聲。\n", environment(me), me);
        }
        else
        {
                tell_object(me, HIB"忽然一陣劇痛襲來，你中暗器的傷口惡化了！\n"NOR );
                message("vision", me->name() + "的臉上突然露出痛苦神情，牙關咬得格格直響。\n", environment(me), me);
        }
        me->receive_wound("qi",15 + random(10),"暗器毒發而死");
        me->receive_wound("jing", 10,"暗器毒發而死");
        if( query("eff_jing", me)<0 || query("eff_qi", me)<0)return 0;
        me->apply_condition("anqi_poison", duration - 1);

        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}

string query_type(object me)
{
        return "poison";
}