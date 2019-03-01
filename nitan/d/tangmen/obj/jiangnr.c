inherit ITEM;
inherit F_FOOD;
#include <ansi.h>

void create()
{
        set_name(HIC "醬牛肉" NOR, ({"rou"}));
        set_weight(50);

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "盤");
                set("long", "這是一盤醬制了三個月的熟牛肉，是下酒的好菜。\n");
                set("value", 0);
                set("food_remaining", 5);
                set("food_supply", 20);
        }
        setup();
}