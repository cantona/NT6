// fish.c 西湖醋魚
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(RED"西湖醋魚"NOR, ({"fish"}));
        set_weight(1300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一盤清甜可人的西湖醋魚，用西湖中的金色鯉魚
燒制而成，是西湖第一名菜。\n");
                set("unit", "碗");
                set("value", 120);
                set("food_remaining", 20);
                set("food_supply", 20);
        }
}