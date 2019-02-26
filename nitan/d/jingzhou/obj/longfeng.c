#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIR"龍鳳配"NOR, ({"longfeng"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "相傳為三國劉備招親而製作的慶筵名菜。鱔作龍，雞作鳳，形態逼真，味道鮮美。\n");
                set("unit", "碗");
                set("value", 500);
                set("food_remaining", 10);
                set("food_supply", 100);
        }
}
