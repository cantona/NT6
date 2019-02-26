// medicine: xuelian.c
// Last Modified by winder on Sep. 27 2001

#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("天山雪蓮", ({"xuelian", "lian", "lotus"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("vegetable", 32);
                set("nostrum", 4);
                set("long", "這是一株只有在寒冷的地方才能生長的雪蓮。\n");
                set("value", 100);
        }
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

        if( query("eff_qi", me) == query("max_qi", me) )
                return notify_fail("你現在不用吃這寶貝！\n");
        me->receive_curing("qi",200);
        message_vision("$N小心地吃下一株雪蓮，頓時覺得神清氣爽了不少！\n", me);
        destruct(this_object());
        return 1;
}
