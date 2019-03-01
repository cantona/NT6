// Code of ShenZhou
// apple 國光蘋果
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("蘋果", ({"ping guo", "guo"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個新鮮香甜的大紅蘋果。\n");
                set("unit", "個");
                set("value", 20);
                set("food_remaining", 3);
                set("food_supply", 10);
        }
}