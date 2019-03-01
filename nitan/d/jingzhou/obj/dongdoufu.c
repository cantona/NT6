#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIC"凍"HIW"豆腐"NOR, ({"dongdoufu", "doufu"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是老通城的著名小吃。\n");
                set("unit", "碗");
                set("value", 100);
                set("food_remaining", 3);
                set("food_supply", 50);
        }
}
