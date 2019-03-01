// xiongdan.c 熊膽

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(GRN"熊膽"NOR, ({"xiong dan", "dan"}));
        set_weight(1000);
        set("vegetable", 16);
        set("value", 2400);
        set("nostrum", 64);
        set("unit", "顆");
        set("long", "這是一顆暗綠色的熊膽，看來可以入藥。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        set("eff_qi",query("max_qi",  me), me);
        message_vision("$N吃下一副熊膽，覺得精神好多了。\n", me);
        destruct(this_object());
        return 1;
}
