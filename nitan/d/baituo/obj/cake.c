#include <ansi.h> 

inherit F_FOOD;
inherit ITEM;

void create()
{
        set_name("蛋糕", ({ "hong bing", "hong", "bing" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "這是一塊香噴噴的大蛋糕。\n" NOR);
                set("unit", "塊");
                set("value", 200);
                set("food_remaining", 4);
                set("food_supply", 20);
        }
        setup();
}