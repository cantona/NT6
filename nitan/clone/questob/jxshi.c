// jxshi.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("雞血石", ({ "jixue shi", "shi" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是一塊暗紅色的雞血石。\n");
                set("value", 1500);
                set("material", "stone");
        }
        setup();
}