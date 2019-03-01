// mj_jail.c
#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{         
               object where;
        if (duration < 2) {
            me->move("/d/mingjiao/shaqiu2");
            message("vision",HIY "你聽到一聲：“快滾，下次別讓我再見到你”。原來是一個全身糟透了的家伙給扔到了沙漠。\n"NOR, environment(me), me);
            tell_object(me, HIY "只覺被人連抬帶拖，你昏昏沉沉地被扔到了沙漠之中！\n" NOR);
            set("startroom", START_ROOM, me);
            return 0;
        } 
 
        where = environment(me);
        if (base_name(where)!="/d/mingjiao/jianyu") {
                message_vision(HIR "突然沖出幾名明教高手，將$N亂棒打暈......\n" NOR, me);
                me->unconcious();
                message_vision("明教高手扛著暈死過去的$N，揚長而去。\n", me);
                me->move("/d/mingjiao/jianyu");
                set("eff_qi", 1, me);
                set("qi", 1, me);
                duration = 120;
        }
        me->apply_condition("mj_jail", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "jail";
}