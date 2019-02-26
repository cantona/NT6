// zhuguo.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "朱果" NOR, ({"zhu guo", "guo"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆朱果，通體鮮紅，一望而知是不"
                            "可多得的珍品。\n");
                set("value", 10000);
                set("no_sell", "這個小紅豆也能拿來賣？\n");
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        set("qi",query("eff_qi",  me), me);
        set("neili",query("max_neili",  me), me);
        message_vision(HIR "$N" HIR "吃下一顆朱果，只覺飢渴全消，一股"
                       "暖流從丹田直衝上來。\n"NOR,me);

        destruct(this_object());
        return 1;
}
