// /d/yixing/obj/tipang.c
// Last Modified by winder on Jul. 12 2002

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("滷豬蹄膀", ({"tipang", "ti"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一盤滷豬蹄膀。\n");
                set("unit", "盤");
                set("value", 0);
                set("food_remaining", 1);
                set("food_supply", 1);
        }
}