// baiwei.c 白薇

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW"白薇"NOR, ({"baiwei"}));
        set_weight(500);
        set("unit", "朵");
        set("value", 1200);
        set("vegetable", 1);
        set("nostrum", 2);
        set("long", "這是一朵盛開的白薇，看來可以入藥。\n");
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

        write("你一口就把白薇吃了下去。\n");
        destruct(this_object());
        return 1;
}