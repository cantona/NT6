//honglian.c 小紅蓮

inherit ITEM;

#include <ansi.h>

void create()
{
        set_name(HIR"小紅蓮"NOR, ({"hong lian", "honglian"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "朵");
                set("long", "這是一朵紅色小花，象極了一個小蓮座。\n");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision("$N把" + name() + "扔進嘴裏，幾下就吞了下去。\n", me);
        addn("neili", 100, me);
        if( query("neili", me)>query("max_neili", me) )
                set("neili",query("max_neili",  me), me);
        destruct(this_object());
        return 1;
}

