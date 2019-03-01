inherit ITEM;
inherit F_FOOD;


void create()
{
        set_name("素餅", ({"su bing","bing"}));
        set_weight(150);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊鬆軟的素餅。\n");
                set("unit", "塊");
                set("value", 4);//很便宜，（基本食物都應該很便宜）.
		set("food_remaining", 10);
		set("food_supply", 60);
        }
}
