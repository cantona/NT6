inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("烤魚", ({"kao yu", "yu"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一條香噴噴的烤魚。\n");
                set("unit", "條");
                set("food_remaining", 4);
                set("food_supply", 30);
        }
}