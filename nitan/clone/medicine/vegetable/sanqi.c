// sanqi.c 三七

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIC"三七"NOR, ({"sanqi"}));
        set_weight(500);
        set("vegetable", 16);
        set("value", 100);
        set("nostrum", 1);
        set("unit", "塊");
        set("long", "這是一塊帶泥的三七，看來可以入藥。\n");
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
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        write("三七是藥材，不能張口就吃。\n");
        return 1;
}