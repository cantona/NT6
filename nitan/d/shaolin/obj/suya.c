// suji.c 素鴨

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("素鴨", ({"suya", "ya"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一隻做工考究素鴨。\n");
                set("unit", "只");
                set("value", 150);
                set("food_remaining", 4);
                set("food_supply", 50);
        }
}