//yangjing.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"養精丹"NOR, ({"yangjing dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "粒");
                set("value", 2000);
        }

        setup();
}

int init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        object me = this_player();
        if (! id(arg)) return notify_fail("你要吃什麼？\n");
        if (me->is_busy())
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");
                message_vision("$N吃下一粒" + name() + "。\n", me);

        if( query("eff_jing", me)/query("max_jing", me)<0.9 )
        {
                me->receive_curing("jing",query("max_jing", me)/50);
        }
        me->start_busy(2);
        destruct(this_object());
        return 1;
}