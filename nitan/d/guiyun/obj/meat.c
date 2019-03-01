// Obj: /d/guiyun/obj/meat.c
// Last Modified by winder on Jul. 9 2001

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("豬肉", ({"rou", "meat"}));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一塊做菜用的生豬肉，還殘留著血絲。\n");
                set("unit", "塊");
                set("value", 0);
                set("food_remaining", 4);
                set("food_supply", 25);
        }
}