// qiancenggao.c

inherit ITEM;
inherit F_FOOD;
#include <ansi.h>;
void create()
{
        set_name(HIG"千層糕"NOR, ({"qianceng gao", "gao"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這千層糕是一層面粉一層蜜糖豬油做成，更有桂花香氣，既鬆且甜。\n");
                set("unit", "塊");
                set("value", 100);
                set("food_remaining", 10);
                set("food_supply", 10);
        }
}
