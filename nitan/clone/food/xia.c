// xia.c 烤蝦

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("烤蝦", ({"kao xia", "xia"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一只紅通通，香噴噴的烤蝦。\n");
                set("unit", "只");
                set("food_remaining", 4);
                set("food_supply", 10);
        }
}