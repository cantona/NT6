// red_rose.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIR "紅玫瑰" NOR, ({"hong meigui", "red rose"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一朵含苞欲放的深紅玫瑰，象徵着美，愛，戀。\n");
                set("unit", "束");
                set("base_value", 30);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower",1);
        }
        set_amount(1);
}
#include "flower.h"