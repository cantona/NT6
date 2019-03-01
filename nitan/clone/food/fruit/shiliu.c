// shiliu.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(HIR"石榴"NOR, ({"shi liu", "shiliu","pomegranate"}));
        set_weight(4000);
        set("long", "一個裂開了口的薄皮大石榴。\n");
        set("unit", "個");
        set("life", 30);
        set("value", 0);
        set("fruit_remaining", 5); //可以吃5口
        set("food_supply", 5);   //每口加5的food
        set("water_supply", 25);  //每口可以加5的water
        //每次吃的msg,沒有也可以的。
        set("eat_msg", "$N拿起$n，剝了幾個籽兒吃下去。\n");
        //最後一口的msg，沒有亦可
        set("end_msg", "$N仔細的剝出最後幾個籽吃下去。\n");  
        //吃飽了的msg, 沒有亦可，但不能有代詞。
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        // 水果吃完剩下的東西 :-)
        set("core", "石榴皮");         //name
        set("core_id", ({"shiliu pi", "pomegranate peel", "pi", "peel"}) ); //id
        set("core_unit", "個");        //unit
        set("core_long", "一個石榴皮。\n"); //long
        set("gifts", ([
                "per" : 1,
                "cps" : 1,
        ]));
        setup();
}
