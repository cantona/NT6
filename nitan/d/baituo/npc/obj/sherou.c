// sherou.c 蛇肉

inherit F_FOOD;
inherit ITEM;

void create()
{
        set_name("蛇肉", ({ "she rou", "rou" }) );
        set_weight(350);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一條燒烤得香噴噴的蛇肉。\n");
                set("unit", "條");
                set("value", 50);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
    setup();
}