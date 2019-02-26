// yangyandan.c 養顏丹
// Last Modified by Winder on Mar. 5 2001

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW"養顏丹"NOR, ({"yangyan dan", "dan"}));
        set("unit", "粒");
        set("vegetable", 0);
        set("nostrum", 0);
        set("level", 300);
        set("long", "這是一粒玉雪可愛的養顏丹。\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        if( query("per", me) >= 40 )
        {
                message_vision("$N沒必要吃養顏丹。\n",me);
        }
        else
        {
                addn("per", 1, me);
                message_vision("$N吃下一粒養顏丹，下意識地伸手摸了摸臉，覺得似乎皺紋是比原來少了點。\n",me);
                destruct(this_object());
        }
        return 1;
}