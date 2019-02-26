// zanghonghua.c 藏紅花

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIR"藏紅花"NOR, ({"zanghonghua"}));
        set_weight(500);
        set("vegetable", 32);
        set("value", 1700);
        set("nostrum", 8);
        set("unit", "朵");
        set("long", "這是一朵來自雪域高原的藏紅花，看來可以入藥。\n");
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

        write("記得韋爵爺説過：戰馬吃了芍藥花，能全身活血。你吃藏紅花圖個啥呦！\n");
        return 1;
}