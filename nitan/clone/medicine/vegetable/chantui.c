// chantui.c 蟬蜕

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"蟬蜕"NOR, ({"chantui"}));
        set_weight(500);
        set("vegetable", 1);
        set("value", 2000);
        set("nostrum", 32);
        set("unit", "片");
        set("long", "這是一片風乾的蟬蜕，看來可以入藥。\n");
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

        write("蟬蜕必須入藥才能吃。\n");
        return 1;
}