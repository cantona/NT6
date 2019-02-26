// liyu.c 糖醋鯉魚

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY "糖醋鯉魚" NOR, ({"tangcu liyu", "liyu"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一盤外焦裏嫩，酸甜適口的糖醋鯉魚。\n");
                set("unit", "盤");
                set("value", 250);
                set("food_remaining", 3);
                set("food_supply", 30);
        }
}