// mangguo.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("芒果", ({"guo", "mangguo"}));
        set_weight(40);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一顆新鮮的芒果，看了讓人垂涎欲滴。\n");
                set("unit", "顆");
                set("value", 80);
                set("food_remaining", 4);
                set("food_supply", 30);
        }
}
