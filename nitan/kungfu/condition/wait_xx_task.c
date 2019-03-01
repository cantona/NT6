// Last Modified by Winder on Apr. 25 2001
// wait_xx_task.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                message_vision(HIW"突然天空中飛下一只白鴿，降在$N的肩頭。\n"NOR, me);
                tell_object(me, HIY"這是一封新的飛鴿傳書，你又可以要求新的任務了！\n"NOR);                
                return 0;
        }
        me->apply_condition("wait_xx_task", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "job";
}
