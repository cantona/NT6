// jugeng.c 菊梗

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(GRN"菊梗"NOR, ({"jugeng"}));
        set_weight(500);
        set("vegetable", 4);
        set("value", 50);
        set("nostrum", 32);
        set("unit", "支");
        set("long", "這是一支蔫了的菊梗，看來可以入藥。\n");
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

        write("菊梗不是這樣吃的。\n");
        return 1;
}