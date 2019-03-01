// jiyu.c 鯽魚

inherit ITEM;

#include <ansi.h>
#include "fish.h";

void create()
{
        set_name("鯽魚", ({ "ji yu", "jiyu" }) );
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "一條活蹦亂跳的大鯽魚。\n");
                set("unit", "條");
        }

        setup();
}