// bonze_jail.c

#include <ansi.h>
#include <login.h>

int update_condition(object me, int duration)
{
        if (duration < 1)
        {
                me->move("/d/shaolin/guangchang1");
                message("vision",
                        HIY "只聽乒地一聲，你嚇了一跳，定睛一看，\n"
                        "原來是一個昏昏沉沉的家伙從大門裡被扔了出來！\n" NOR, environment(me), me);
                tell_object(me, HIY "只覺一陣騰雲駕霧般，你昏昏沉沉地被扔出了少林寺！\n" NOR);
                me->set("startroom", START_ROOM);
                return 0;
        }

        me->apply_condition("bonze_jail", duration - 1);
        return 1;
}
