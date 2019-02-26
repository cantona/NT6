// fuling.c 茯苓

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"茯苓"NOR, ({"fuling"}));
        set_weight(500);
        set("vegetable", 2);
        set("value", 100);
        set("nostrum", 8);
        set("unit", "塊");
        set("long", "這是一塊成型的茯苓，看來可以入藥。\n");
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

        write("你三口兩口把茯苓吃了下去。\n");
        destruct(this_object());
        return 1;
}