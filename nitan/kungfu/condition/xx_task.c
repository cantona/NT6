// Last Modified by Winder on Apr. 25 2001
// xx_task.c

#include <ansi.h>

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                message_vision(HIW"突然天空中飛下一只白鴿，降在$N的肩頭。\n"NOR, me);
                if( query_temp("job_type", me) == 1 )
                        tell_object(me,BLU"這是一封飛鴿傳書，原來老仙已經對殺不殺「"+query_temp("xx_target", me)+"」的事不感興趣了！\n"NOR);
                else if( query_temp("job_type", me) == 2 )
                        {
                                tell_object(me,BLU"這是一封飛鴿傳書，原來老仙已經對「"+query_temp("xx_target", me)+"」不感興趣了！\n"NOR);
                                if( query("xx_points", me)>10 )
                                        addn("xx_points", -1, me);
                                delete_temp("xx_bonus", me);
                                delete_temp("xx_time", me);
                                delete_temp("xx_pot", me);
                                delete_temp("job_id", me);
                                me->clear_condition("xx_task");
                                delete_temp("xx_target", me);
                                me->apply_condition("wait_xx_task", 10);
                                return 0;
                        }
                delete_temp("xx_bonus", me);
                delete_temp("xx_time", me);
                delete_temp("xx_pot", me);
                delete_temp("job_id", me);
                me->clear_condition("xx_task");
                delete_temp("xx_target", me);
                me->apply_condition("wait_xx_task", 10);
                return 0;
        }
        me->apply_condition("xx_task", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "job";
}
