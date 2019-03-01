#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIB"猴頭"HIM"芙蓉"NOR, ({"houtou"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是“四季美飯莊”的一道名菜，香噴噴地冒著熱氣。\n");
                set("unit", "盤");
                set("value", 1000);
                set("food_remaining", 10);
                set("food_supply", 50);
        }
}
