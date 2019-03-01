// shit.c 狗屎

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}
void create()
{
        set_name(YEL"狗屎"NOR, ({"shit"}));
        set("unit", "堆");
        set("value", 0);
        set("long", "這是一堆臭狗屎，不知道是誰拉的。\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("你要吃什麼？\n");
        if(!present(this_object(), me))
                return notify_fail("你要吃什麼？\n");
        if( me->is_busy() )
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        if(arg=="shit") 
                return notify_fail("這你也能吃？真是佩服啊佩服！\n");
        me->start_busy(2);
        return 1;
}