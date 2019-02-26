// mantou.c 饅頭

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("白麪饅頭", ({ "mantou" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個香噴噴的白麪饅頭。\n");
                set("unit", "個");
                set("value", 10);
                set("food_remaining", 4);
                set("food_supply", 30);
        }
}