// gaoyao.c

inherit ITEM;
#include <ansi.h>

void setup()
{}

void init()
{
        add_action("do_tie", "tie");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"狗皮膏藥"NOR, ({"goupi gaoyao", "goupi", "gaoyao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "帖");
                set("long", "這是一帖武林人士常貼(tie)的狗皮膏藥。\n");
                set("value", 5000);
        }
        set("pour_type", "1");
        setup();
}

int do_tie(string arg)
{
        object me = this_player();

        if (!id(arg)) return notify_fail("你要貼什麼藥？\n");
        if (!present(this_object(), this_player()))
                return notify_fail("你要貼什麼藥？\n");
        if (me->is_busy() )
                return notify_fail("現在你沒空貼狗皮膏藥了。\n");

        if( query("eff_qi", me) == query("max_qi", me) )
                return notify_fail("你現在不需要用狗皮膏藥。\n");
        else {
                me->receive_curing("qi", 50);
                message_vision("$N啪的一聲在傷口上貼了一帖狗皮膏藥，氣色看起來好多了。\n", me);
                me->start_busy(2);
                destruct(this_object());
                return 1;
        }
}
