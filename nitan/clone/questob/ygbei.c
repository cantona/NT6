// ygbei.c

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("夜光杯", ({ "ye guangbei", "cup", "bei" }));
        set_weight(400);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "這是一只翡翠質地的酒杯。\n");
                set("value", 10000);
                set("material", "jade");
        }
        setup();
}