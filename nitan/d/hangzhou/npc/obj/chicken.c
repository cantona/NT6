// chicken.c
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;
void create()
{
        set_name(YEL"叫化童雞"NOR, ({"chicken"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("long", "一隻被烤得流油，香味撲鼻的叫化雞。\n");
                set("unit", "只");
                set("value", 120);
                set("food_remaining", 1);
                set("food_supply", 100);
        }
}