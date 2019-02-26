// heye.c 荷葉

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIG"荷葉"NOR, ({"heye"}));
        set_weight(500);
        set("vegetable", 4);
        set("value", 5);
        set("nostrum", 2);
        set("unit", "片");
        set("long", "這是一片碧綠的荷葉，看來可以入藥。\n");
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

        write("吃荷葉？你不會餓到吃葉子的水平吧？\n");
        return 1;
}