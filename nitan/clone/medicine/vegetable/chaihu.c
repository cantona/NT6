// chaihu.c 柴胡

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(CYN"柴胡"NOR, ({"chaihu"}));
        set_weight(500);
        set("vegetable", 1);
        set("value", 400);
        set("nostrum", 16);
        set("unit", "支");
        set("long", "這是一支加工過的柴胡，看來可以入藥。\n");
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

        write("你三口兩口就把柴胡吃了下去。\n");
        destruct(this_object());
        return 1;
}