// qingyu.c 青魚

inherit ITEM;

#include <ansi.h>
#include "fish.h"

void create()
{
        set_name("青魚", ({ "qingyu", "qing yu" }) );
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "一條不安分的青魚。\n");
                set("unit", "條");
        }

        setup();
}