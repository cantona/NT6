// xitang.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIR"喜糖"NOR, ({"xi tang", "tang"}));
        set("unit", "包");
        set("value",10000);
        set("long", "這是一包「俠客行一百」飛雪堂特製的精美喜糖。\n");
        set("amount",100);
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
        message_vision(NOR"$N把一包"HIR"喜糖"NOR"吃個精光，分享了新郎新娘的甜蜜與温馨。\n",me);

        destruct(this_object());
        return 1;
}