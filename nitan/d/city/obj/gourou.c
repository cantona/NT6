// turou.c 紅燒狗肉

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("紅燒狗肉", ({"gou rou", "gou"}));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香噴噴的紅燒狗肉\n");
                set("unit", "碗");
                set("value", 200);
                set("food_remaining", 4);
                set("food_supply", 50);
        }
}