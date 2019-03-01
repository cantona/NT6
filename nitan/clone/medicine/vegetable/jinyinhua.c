// jinyinhua.c 金銀花

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"金"HIW"銀"HIY"花"NOR, ({"jinyinhua"}));
        set_weight(500);
        set("vegetable", 4);
        set("value", 30);
        set("nostrum", 16);
        set("unit", "根");
        set("long", "這是一根的金銀花，看來可以入藥。\n");
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

        write("金銀花入藥才能入口。\n");
        return 1;
}