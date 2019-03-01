// hongshao-qiezi.c 紅燒茄子
// Last Modified by Sir on May. 22 2001

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("紅燒茄子", ({"hongshao qiezi","qiezi"}));
        set_weight(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一盆青紅相間，金黃透爛，清香四溢的紅燒茄子。\n");
                set("unit", "盆");
                set("value", 150);
                set("food_remaining", 4);
                set("food_supply", 40);
        }
}