// caoyu.c 草魚

inherit ITEM;

#include <ansi.h>
#include "fish.h"

void create()
{
        set_name("草魚", ({ "caoyu", "cao yu" }) );
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "一條活蹦亂跳的草魚。\n");
                set("unit", "條");
        }

        setup();
}