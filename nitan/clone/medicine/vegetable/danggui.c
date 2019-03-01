// danggui.c 當歸

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"當歸"NOR, ({"danggui"}));
        set_weight(500);
        set("vegetable", 2);
        set("value", 300);
        set("nostrum", 2);
        set("unit", "塊");
        set("long", "這是一塊烘幹過的當歸，看來可以入藥。\n");
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

        write("你三口兩口就把當歸吃了下去。\n");
        destruct(this_object());
        return 1;
}