// lurong.c 鹿茸

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"鹿茸"NOR, ({"lurong"}));
        set_weight(500);
        set("vegetable", 8);
        set("value", 12000);
        set("nostrum", 4);
        set("unit", "副");
        set("long", "這是一副梅花鹿的鹿茸，看來可以入藥。\n");
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

        write("鹿茸不能這麼吃的。\n");
        return 1;
}