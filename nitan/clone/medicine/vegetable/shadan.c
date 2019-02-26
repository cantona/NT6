// shadan.c 熊膽

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIG"鯊膽"NOR, ({"shadan", "dan"}));
        set_weight(1000);
        set("vegetable", 16);
        set("value", 7000);
        set("nostrum", 2);
        set("unit", "顆");
        set("long", "這是一顆碧綠的鯊膽，看來可以入藥。\n");
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

        set("eff_qi",query("max_qi",  this_player()), me);
        message_vision("$N吃下一副鯊膽，覺得精神好多了。\n", me);
        destruct(this_object());
        return 1;
}
