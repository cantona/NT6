// geng.c
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIR"桂花鮮栗羹"NOR, ({"Guihua geng", "guihua", "geng"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香氣馥鬱的桂花鮮栗羹。\n");
                set("unit", "碗");
                set("value", 120);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
}