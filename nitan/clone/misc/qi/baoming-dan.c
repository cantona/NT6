
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "天王保命丹" NOR, ({"baoming dan", "baoming", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", HIR "一顆紅色的藥丸。恢復全部氣血和最大氣血。\n" NOR);
                set("value", 100000);
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

        message_vision(HIR "$N" HIR "吃下一顆天王保命丹，只覺舒泰之極！\n" NOR, me);

        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("max_qi"));

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
