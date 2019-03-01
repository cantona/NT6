// hsnr.c 紅燒牛肉

inherit ITEM;
inherit F_FOOD;

void create()
{
    set_name("紅燒牛肉", ({"hongshao niurou", "niurou"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
        set("long", "一盤燉得很爛很香的牛肉，看得你直流口水。\n");
        set("unit", "盤");
                set("value", 150);
                set("food_remaining", 3);
                set("food_supply", 60);
        }
}