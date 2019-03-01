// badou.c 巴豆

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIG"巴豆"NOR, ({"badou"}));
        set_weight(500);
        set("unit", "粒");
        set("vegetable", 1);
        set("value", 1000);
        set("nostrum", 1);
        set("long", "這是一粒綠油油的巴豆，看來可以入藥。\n");
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

        write("你一口就把巴豆吃了下去。結果蹲下就拉，拉得頭暈眼花。\n");
        set("qi", 1, me);
        destruct(this_object());
        return 1;
}