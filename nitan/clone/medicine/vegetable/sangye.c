// sangye.c 桑葉

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIG"桑葉"NOR, ({"sangye"}));
        set_weight(500);
        set("vegetable", 8);
        set("value", 15);
        set("nostrum", 64);
        set("unit", "片");
        set("long", "這是一片烤乾的桑葉，看來可以入藥。\n");
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

        write("你既不是吐絲的蠶，也不是吃草的兔子，怎麼對這有興趣？\n");
        return 1;
}