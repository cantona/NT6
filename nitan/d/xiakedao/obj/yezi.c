// yezi.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("椰子", ({"ye", "yezi"}));
        set_weight(40);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一顆新鮮的椰子，看了讓人垂涎欲滴。\n");
                set("unit", "顆");
                set("value", 80);
                set("food_remaining", 4);
                set("food_supply", 30);
        }
}
