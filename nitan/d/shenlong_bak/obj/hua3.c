// hua3.c

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIR "斷腸花" NOR, ({"hua3","duanchang"}));
        set("unit", "朵");
        set("long", "這是一朵斷腸花，通體通紅，鮮嫩欲滴，美麗異常。\n");
        set("no_get", "你根本不敢近前。\n");
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
        if(random(2)==0) this_player()->unconcious();
        else this_player()->die();
        destruct(this_object());
        return 1;
}