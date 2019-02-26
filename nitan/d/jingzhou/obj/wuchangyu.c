#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY"松子"HIR"武昌魚"NOR, ({"wuchang yu"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是“四季美飯莊”的一道名菜，用新鮮武昌魚烹製而成，香噴噴地冒着熱氣。\n");
                set("unit", "盤");
                set("value", 800);
                set("food_remaining", 10);
                set("food_supply", 100);
        }
}
