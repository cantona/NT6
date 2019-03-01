// xionghuang.c 雄黃

inherit ITEM;
#include <ansi.h>

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIY"雄黃"NOR, ({"xiong huang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("vegetable", 32);
                set("nostrum", 1);
                set("long", "這是一包雄黃，據說可驅百毒。\n");
                set("value", 1000);
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
                return notify_fail("別急，慢慢吃，小心別噎著了。\n");

        return notify_fail("想死啊？雄黃不能吃。\n");
}
