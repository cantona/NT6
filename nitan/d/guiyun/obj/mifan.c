// Obj: /d/guiyun/obj/mifan.c
// Last Modified by winder on Jul. 9 2001

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("大米飯", ({"dami fan", "mifan", "fan"}));
        set_weight(40);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香噴噴的大米飯。\n");
                set("unit", "碗");
                set("value", 0);
                set("food_remaining", 5);
                set("food_supply", 40);
        }
}