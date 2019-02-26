// renshen.c 人蔘

inherit ITEM;
#include <ansi.h>;
void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIY"人蔘"NOR, ({"ren shen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("vegetable", 8);
                set("nostrum", 32);
                set("long", "這是一株保存了很久的千年人蔘。\n");
                set("value", 10000);
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

        me->receive_curing("qi", 200);
        message_vision("$N吃下一株人蔘，頓覺渾身一股熱氣兜底冒了上來！\n",me);
        destruct(this_object());
        return 1;
}
