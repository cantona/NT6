// fotiaoqiang.c
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(RED"佛跳牆"NOR, ({"fotiaoqiang"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香噴噴的佛跳牆，是福建第一名菜。\n");
                set("unit", "碗");
                set("value", 500);
                set("food_remaining", 10);
                set("food_supply", 100);
        }
}