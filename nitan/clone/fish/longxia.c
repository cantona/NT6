// longxia.c 龍蝦

inherit ITEM;

#include <ansi.h>
#include "xia.h";

void create()
{
        set_name("龍蝦", ({ "long xia", "longxia" }) );
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "一只威武的大龍蝦。\n");
                set("unit", "只");
        }

        setup();
}