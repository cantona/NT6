// liji.c 抓炒裏脊

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(HIY "抓炒裏脊" NOR, ({"zhuachao liji", "liji"}));
        set_weight(400);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "抓炒裏脊酸、鹹、甜，外焦裏嫩，是“四大抓炒”之一。\n");
                set("unit", "碟");
                set("value", 100);
                set("food_remaining", 1);
                set("food_supply", 50);
        }
}