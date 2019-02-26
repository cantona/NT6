// lingzhi1.c 靈脂

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIG"靈脂"NOR, ({"lingzhi"}));
        set_weight(500);
        set("vegetable", 8);
        set("value", 1200);
        set("nostrum", 2);
        set("unit", "塊");
        set("long", "這是一塊海豹的靈脂，看來可以入藥。\n");
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

        write("靈脂不能生吃。\n");
        return 1;
}