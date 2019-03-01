// paigu.c 烤鴨

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("無錫醬排骨", ({"jiang paigu", "paigu"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊噴香的無錫醬排骨。\n");
                set("unit", "塊");
                set("value", 150);
                set("food_remaining", 3);
                set("food_supply", 60);
        }
}