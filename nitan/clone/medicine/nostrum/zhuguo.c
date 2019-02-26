// zhuguo.c
#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
        if (!wizardp(this_player()))
        {
                set("no_get", "嘿嘿，做夢吧！\n");
                set("no_drop", "朱果你都想扔？\n");
        }
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIR "朱果" NOR, ({"zhu guo", "guo"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆朱果，通體鮮紅，一望而知是不可多得的珍品。\n");
                set("value", 10000);
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
                return notify_fail("別急，慢慢吃，小心別噎着了。\n");

        set("qi",query("eff_qi",  me), me);
        set("neili",query("max_neili",  me), me);
        message_vision(HIR "$N吃下一顆朱果，只覺飢渴全消，一股暖流從丹田直衝上來。\n"NOR,me);
        destruct(this_object());
        return 1;
}