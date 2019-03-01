// poison: shedan.c
// Last Modified by winder on Jul. 12 2002

inherit ITEM;
#include <ansi.h>;
int cure_ob(string);

void create()
{
        set_name("毒蛇膽", ({"shedan", "dan"}));
        set("unit", "粒");
        set("long", "這是一只綠瑩瑩的毒蛇膽。\n");
        set("value", 200);
        set("medicine", 1);
        setup();
}
int do_eat(string arg)
{
        int taoism_limit, jingli_limit;
        object me = this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if ((int)me->query_condition("snake_poison") > 7)
        {
                me->apply_condition("snake_poison", (int)me->query_condition("snake_poison") - 5);
        }
        message_vision("$N吃下一副毒蛇膽，一不小心咬破了，好苦哦。\n",me);
        destruct(this_object());
        return 1;
}
