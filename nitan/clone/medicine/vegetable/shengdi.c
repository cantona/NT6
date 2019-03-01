// shengdi.c 生地

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(BLK"生地"NOR, ({"shengdi"}));
        set_weight(500);
        set("vegetable", 16);
        set("value", 500);
        set("nostrum", 4);
        set("unit", "塊");
        set("long", "這是一塊不起眼的生地，看來可以入藥。\n");
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

        write("生地你也吃？佩服佩服！\n");
        return 1;
}