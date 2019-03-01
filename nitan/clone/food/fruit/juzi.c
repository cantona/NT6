// juzi.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
        set_name(YEL"橘子"NOR, ({"ju zi", "juzi","orange"}));
        set_weight(4000);
        set("long", "一個圓圓的金黃色的大橘子。\n");
        set("unit", "個");
        set("life", 20);
        set("value", 0);
        set("fruit_remaining", 3); 
        set("food_supply", 5);   
        set("water_supply", 25);
        set("eat_msg", "$N拿起$n，剝了幾個瓣兒吃下去。\n");
        set("end_msg", "$N剝出最後一瓣$n吃下去。\n");  
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        set("core", "橘子皮");   
        set("core_id", ({"juzi pi", "orange peel", "pi", "peel"}) ); //id
        set("core_unit", "個");   //unit
        set("core_long", "一個橘子皮。\n"); //long
        set("gifts", ([
                "per" : 1,
                "int" : 1,
        ]));

        setup();
}
