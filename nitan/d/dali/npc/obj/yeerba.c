// guoqiaomixian.c

inherit ITEM;
inherit F_FOOD;
#include <ansi.h>;

void create()
{
        set_name(HIG"葉兒粑"NOR, ({"ye er ba", "ba"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一塊飄着清香的葉ㄦ粑。\n");
                set("unit", "碗");
                set("value", 100);
                set("food_remaining", 15);
                set("food_supply", 20);
        }
}