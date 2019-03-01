// renshenguo.c
inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name(HIR"人參果"NOR, ({"guo", "renshen guo"}));
        set("unit", "朵");
        set("long", "這是一只人參果, 已經成型, 真的象極了三周不滿的小孩。\n");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();
        if (!id(arg))  return notify_fail("你要吃什麼？\n");
        if(arg=="guo")
        {
                addn("max_neili", 10, me);
                set("neili",query("max_neili",  me), me);
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                message_vision("$N吃下一枚人參果，只覺得精神健旺，氣血充盈，體內真力源源滋生，甚至不再感到饑餓幹渴!\n",me);

                destruct(this_object());
        }
        return 1;
}
