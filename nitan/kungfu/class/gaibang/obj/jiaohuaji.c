// jiaohuaji.c 叫化雞

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("叫化雞", ({"jiaohua ji", "ji"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一隻被烤得流油，香味撲鼻的叫化雞。\n");
                set("unit", "只");
                set("value", 200);
                set("food_remaining", 1);
                set("food_supply", 100);
        }
}