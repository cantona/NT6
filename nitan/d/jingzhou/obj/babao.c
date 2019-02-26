#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIC"荊州"HIR"八"HIY"寶"NOR, ({"babao"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "以精選糯米和各種果料烹製而成的八寶飯。\n");
                set("unit", "碗");
                set("value", 100);
                set("food_remaining", 3);
                set("food_supply", 50);
        }
}
