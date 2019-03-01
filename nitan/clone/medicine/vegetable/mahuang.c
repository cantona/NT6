// mahuang.c 麻黃

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIY"麻黃"NOR, ({"mahuang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("vegetable", 32);
                set("value", 100);
                set("nostrum", 16);
                set("long", "這是一包麻黃，據說可以入藥。\n");
                set("value", 1000);
        }
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

        write("麻黃不能這麼吃。\n");
        return 1;
}