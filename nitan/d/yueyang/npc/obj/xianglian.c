// xiangliangeng.c 湘蓮羹

#include <ansi.h>;
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY"湘蓮羹"NOR, ({"xianglian geng", "geng"}));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一碗用湖南洞庭湖的蓮子熬的羹湯。\n");
                set("unit", "碗");
                set("value", 100);
                set("food_remaining", 10);
                set("food_supply", 10);
        }
}