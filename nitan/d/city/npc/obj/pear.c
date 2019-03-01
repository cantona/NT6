// Code of ShenZhou
// pear 錫山鴨梨
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("鴨梨", ({"ya li", "li", "pear"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個新鮮香甜的鴨梨。\n");
                set("unit", "個");
                set("value", 20);
                set("food_remaining", 2);
                set("food_supply", 15);
        }
}