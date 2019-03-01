inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("叫化雞", ({ "jiaohua ji", "jiaohua", "ji" }));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一只被烤得流油，香味撲鼻的叫化雞。\n");
                set("unit", "只");
                set("value", 200);
                set("food_remaining", 50);
                set("food_supply", 100);
        }
}