// shibing.c 柿餅

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("柿餅", ({"shi bing", "bing"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個好甜的柿餅。\n");
                set("unit", "個");
                set("value", 20);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
}