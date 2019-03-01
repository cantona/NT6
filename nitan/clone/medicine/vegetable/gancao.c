// gancao.c 甘草

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIY"甘草"NOR, ({"gancao"}));
        set_weight(500);
        set("vegetable", 2);
        set("value", 10);
        set("nostrum", 16);
        set("unit", "支");
        set("long", "這是一支切短了的甘草，看來可以入藥。\n");
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

        write("你一口就把甘草吃了下去。覺得有一點點甜。\n");
        destruct(this_object());
        return 1;
}