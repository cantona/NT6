#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIW"玉笛誰家聽落梅"NOR, ({"dish"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一碗炙牛肉條，每條牛肉都是由四條小肉條拼成，形如笛子。\n");
                set("unit", "碗");
                set("value", 120);
                set("food_remaining", 16);
                set("food_supply", 30);
        }
}
