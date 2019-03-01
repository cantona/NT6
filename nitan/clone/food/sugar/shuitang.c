// shuitang.c

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(RED"水晶糖"NOR, ({"shuijing tang","tang"}));
        set_weight(150);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "晶瑩圓潤的透明糖塊。\n");
                set("unit", "塊");
                set("value", 20);//很便宜，（基本食物都應該很便宜）.
                set("food_remaining", 3);
                set("food_supply", 10);//正常飯量的人一頓吃二斤。
        }
}
