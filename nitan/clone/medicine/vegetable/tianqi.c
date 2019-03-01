// tianqi.c 田七

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIY"田七"NOR, ({"tianqi"}));
        set_weight(800);
        set("vegetable", 16);
        set("value", 550);
        set("nostrum", 32);
        set("unit", "根");
        set("long", "這是一根田七，看來可以入藥。\n");
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

        write("你三口兩口把田七吃了下去。\n");
        destruct(this_object());
        return 1;
}