// gouzhizi.c 枸枳子

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIR"枸枳子"NOR, ({"gouzhizi"}));
        set_weight(500);
        set("vegetable", 2);
        set("value", 30);
        set("nostrum", 32);
        set("unit", "粒");
        set("long", "這是一粒陳年的枸枳子，看來可以入藥。\n");
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

        write("枸枳子入藥才能吃。\n");
        return 1;
}