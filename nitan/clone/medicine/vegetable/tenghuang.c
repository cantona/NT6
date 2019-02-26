// tenghuang.c 藤黃

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"藤黃"NOR, ({"tenghuang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("vegetable", 32);
                set("value", 350);
                set("nostrum", 32);
                set("long", "這是一包藤黃，據説可以入藥。\n");
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
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        write("你不能這樣吃藤黃。\n");
        return 1;
}