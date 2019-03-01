// nbonze_jail.c 南少林監獄

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        if (duration < 1) {
                me->move("/d/nanshaolin/shanmen");
                message("vision", HIY"只聽乒地一聲，你嚇了一跳，定睛一看，\n原來是一個昏昏沉沉的家伙從大門裡被扔了出來！\n" NOR, environment(me), me);
                tell_object(me, HIY"只覺一陣騰雲駕霧般，你昏昏沉沉地被扔出了南少林寺！\n" NOR);
                set("startroom", START_ROOM, me);
                return 0;
        }
//        tell_object(me, "debug: " + duration + " beats more to go...\n");
        me->apply_condition("nbonze_jail", duration - 1);
        return 1;
}

string query_type(object me)
{
        return "jail";
}