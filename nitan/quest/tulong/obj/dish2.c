#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIG"歲寒三友"NOR, ({"dish"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "鬆仁加上酸梅、竹筍做成，一碟別出心裁的小菜。\n");
                set("unit", "碟");
                set("value", 120);
                set("food_remaining", 10);
                set("food_supply", 30);
        }
}