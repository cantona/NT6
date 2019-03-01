//jinchuangyao.c

inherit ITEM;

#include <ansi.h>

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}
void create()
{
        set_name(HIY"金創藥"NOR, ({"jinchuang yao", "jinchuang", "yao"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "包");
                set("long", "這是一包武林人士必備的金創藥。\n");
                set("value", 5000);
        }
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
        if (! id(arg))
                return notify_fail("你要吃什麼藥？\n");
        if (me->is_busy())
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");
        if( query("eff_qi", me) == query("max_qi", me) )
                return notify_fail("你現在不需要用金創藥。\n");
        else 
        {
                me->receive_curing("qi", 50);
                message_vision("$N吃下一包金創藥，氣色看起來好多了。\n", me);
                me->start_busy(2);
                destruct(this_object());
                return 1;
        }
}