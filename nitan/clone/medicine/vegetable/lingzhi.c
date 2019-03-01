// lingzhi.c 靈芝

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(MAG"靈芝"NOR, ({"lingzhi"}));
        set_weight(500);
        set("vegetable", 8);
        set("value", 10000);
        set("nostrum", 1);
        set("unit", "朵");
        set("long", "這是一朵才摘不久的靈芝，看來可以入藥。\n");
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

        write("你三口兩口就把靈芝吃了下去。漸漸覺得身上有了力氣。\n");
        set("qi",query("eff_qi",  me), me);
        destruct(this_object());
        return 1;
}