// birdie.c

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("鳥肉", ({"niao", "bird"}));
        set_weight(40);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊噴香的鳥肉，真讓人嘴饞。\n");
                set("unit", "塊");
                set("value", 180);
                set("food_remaining", 5);
                set("food_supply", 50);
        }
}
