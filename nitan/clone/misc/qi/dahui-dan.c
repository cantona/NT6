
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "大回丹" NOR, ({"dahui dan", "dahui", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", HIR "一顆黑色的藥丸。恢復600點氣血和最大氣血。\n" NOR);
                set("value", 10000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        if (time() - me->query_temp("last_eat_p1") < 600)
        {
                write("你剛吃過藥，藥力還沒有完全吸收。\n");
                return 1;
        }
        me->set_temp("last_eat_p1", time());

        message_vision(HIR "$N" HIR "吃下一顆大回丹，只覺舒泰之極！\n" NOR, me);

        if (me->query("max_qi") - me->query("eff_qi") <= 600)
        {
                 me->set("eff_qi", me->query("max_qi"));
                 if (me->query("max_qi") - me->query("qi") <= 600)
                        me->set("qi", me->query("max_qi"));
                 
                 else 
                        me->add("qi", 600);  
        }


        else 
        {
                me->add("eff_qi", 600);
                me->add("qi", 600);
        }

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
