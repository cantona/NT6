// hugu.c 虎骨

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(YEL"虎骨"NOR, ({"hugu"}));
        set_weight(500);
        set("vegetable", 4);
        set("value", 30000);
        set("nostrum", 4);
        set("unit", "塊");
        set("long", "這是一塊熬製過的虎骨，看來可以入藥。\n");
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

        write("狗才啃骨頭。你不是吧？\n");
        return 1;
}