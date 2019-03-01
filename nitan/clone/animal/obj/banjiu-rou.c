// banjiu-rou.c 斑鳩肉
// Last Modified by winder on Aug. 1 2002

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name("斑鳩肉", ({"banjiu rou", "bird meat"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一隻死的斑鳩。\n");
                set("unit", "只");
                set("value", 20);
                set("food_remaining", 1);
                set("food_supply", 40);
//                set("food_race","野獸");
        }
}