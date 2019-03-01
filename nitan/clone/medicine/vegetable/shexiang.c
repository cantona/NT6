// shexiang.c 麝香

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIB"麝香"NOR, ({"shexiang"}));
        set_weight(500);
        set("vegetable", 16);
        set("value", 1600);
        set("nostrum", 8);
        set("unit", "塊");
        set("long", "這是一塊香氣馥鬱的麝香，看來可以入藥。\n");
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

        write("麝香沒這種吃法。\n");
        return 1;
}