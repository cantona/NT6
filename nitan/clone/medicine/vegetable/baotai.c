// baotai.c 豹胎

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIM"豹胎"NOR, ({"baotai"}));
        set_weight(500);
        set("unit", "塊");
        set("value", 12000);
        set("vegetable", 1);
        set("nostrum", 8);
        set("long", "這是一塊成型的豹胎，看來可以入藥。\n");
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

        write("豹胎要配藥吃。\n");
        return 1;
}