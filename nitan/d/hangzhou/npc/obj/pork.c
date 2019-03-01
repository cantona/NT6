// pork.c 東坡肉
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(RED"東坡肉"NOR, ({"pork"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香噴噴的東坡肉，用文火煨肥豬肉而成，
蘇東坡在牧守杭州時看到民間吃肉而燒制不得法，遺惠此法至千年以下。\n");
                set("unit", "碗");
                set("value", 120);
                set("food_remaining", 10);
                set("food_supply", 100);
        }
}