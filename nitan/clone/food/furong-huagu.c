// furong-huagu.c 芙蓉花菇

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("芙蓉花菇", ({"furong huagu", "huagu"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一盆湯稠汁濃，味滑爽口的芙蓉花菇湯。\n");
                set("unit", "盆");
                set("value", 150);
                set("food_remaining", 4);
                set("food_supply", 40);
        }
}