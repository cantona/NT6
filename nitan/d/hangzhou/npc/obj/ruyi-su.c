// food by ruri
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIM"如意酥"NOR, ({"ruyi su", "su"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊玫瑰色的點心，據說是紅娘親手做的，不知是真是假？\n");
                set("unit", "塊");
                set("value", 5000);
                set("food_remaining", 3);
                set("food_supply", 20);
        }
}