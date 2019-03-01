// by Lonely

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;

int update_condition(object me, int duration)
{
        int i;
        object *ob;     

        if (duration == 1)
        {
                set_temp("die_reason", "劇毒攻心死了", me);
                tell_object(me, HIB "忽然全身氣血倒流，劇毒攻心，看來已經沒救了！\n" NOR );
                message("vision", me->name() +"的身體一震，神色發散，七竅開始向外流血。\n", environment(me), me);
                me->receive_wound("jing",query("max_jing", me)*4);
                me->receive_damage("qi",query("max_qi", me)*4);
        }
        if (! living(me) && (duration != 1)) 
        {
                message("vision", me->name() + "痛苦地哼了一聲。\n", environment(me), me);
        } else 
        {
                if (duration > 1 && random(10) > 6) 
                {
                        switch(random(2)) 
                        {
                        case(0):       
                                tell_object(me, HIB "你體內毒力發作，真氣發散，行動不受控制\n" NOR );
                                message("vision", me->name() + "的目光散亂，神色異常，可怕地笑了一下。\n",
                                        environment(me), me);
                                ob = all_inventory(environment(me));
                                for(i = 0; i < sizeof(ob); i++) 
                                {
                                        if( query("race", ob[i]) == "人類" && ob[i] != me )
                                        {
                                                message_vision(HIR "$N發狂似的大吼一聲，失魂落魄的攻擊起來！\n" NOR, me);
                                                me->want_kill(ob[i]);
                                                me->kill_ob(ob[i]);
                                                ob[i]->fight_ob(me);
                                        }       
                                }
                                break;
                        case(1):
                                set_temp("die_reason", "劇毒攻心死了", me);
                                tell_object(me, HIB "忽然肺腑一陣劇痛，你體內的毒力發作了！\n" NOR );
                                message("vision",  me->name() +"的目光散亂，神色異常，臉上泛出一層黑氣。\n", environment(me), me);
                                me->receive_damage("qi", 50);
                                me->receive_wound("jing", 30);
                                break;

                        }
                }
 
        }
        me->apply_condition("hua_poison", duration - 1);

        if (duration < 1) return 0;

        return CND_CONTINUE;
}
