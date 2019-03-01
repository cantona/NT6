// cao.c
inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIG"通天草"NOR, ({"tongtian cao","cao"}));
        set("unit", "根");
        set("long", "這是一支碧綠小草，細細長長的。\n");
        setup();
}