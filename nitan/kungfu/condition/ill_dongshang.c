// ill_dongshang.c

#include <ansi.h>
#include <condition.h>

inherit ILLNESS;

string name() { return "ill_dongshang"; }

int min_qi_needed() { return 10; }

int update_condition(object me, int duration)
{
        if( duration < 1 ) return 0;

        message("vision", HIG + me->name() + "的肢體僵"
                          "直青腫，看來被凍傷了。\n" NOR,
                environment(me), me);

        if( !living(me) && me->query("qi") < 1 ) {
                me->set_temp("die_reason", "被活活凍死了");
                me->die();
                return 0;
        }
        else
                tell_object(me, HIB "你覺得肢體末端一陣僵直，看來是被凍傷了！\n" NOR );

        me->receive_wound("qi", 1);
        me->receive_damage("qi", 1);
        me->apply_condition(name(), duration - 1);

        if( duration < 1 ) return 0;
        return CND_CONTINUE;
}
