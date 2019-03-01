// guijia.c 烏龜甲

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIB"烏龜甲"NOR, ({"gui jia","jia"}));
        set_weight(800);
        set("vegetable", 2);
        set("value", 300);
        set("nostrum", 64);
        set("unit", "塊");
        set("long", "這是一塊烏龜甲，上面有各種花紋，看來可以入藥。\n");
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

        write("你不能這樣就啃龜甲。\n");
        return 1;
}