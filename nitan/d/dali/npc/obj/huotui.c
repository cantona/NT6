// huotui.c

inherit ITEM;
inherit F_FOOD;
#include <ansi.h>;

void create()
{
        set_name(HIR"宣威火腿"NOR, ({"xuanwei huotui", "huotui"}));
        set_weight(280);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一塊用蜜餞蓮子煮過，流着紅油的香噴噴的宣威火腿。\n");
                set("unit", "塊");
                set("value", 200);
                set("food_remaining", 10);
                set("food_supply", 30);
        }
}