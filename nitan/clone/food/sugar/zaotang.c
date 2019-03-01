// zao.c

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(WHT"灶糖"NOR, ({"zao tang","tang"}));
        set_weight(150);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "吃起來粘牙的給灶王爺吃的灶糖。\n");
                set("unit", "塊");
                set("value", 20);//很便宜，（基本食物都應該很便宜）.
                set("food_remaining", 3);
                set("food_supply", 10);//正常飯量的人一頓吃二斤。
        }
}