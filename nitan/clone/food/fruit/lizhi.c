// lizhi.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(RED"荔枝"NOR, ({"li zhi", "lizhi", "litchi"}));
        set_weight(4000);
        set("long", "一捧紅艷艷的荔枝。\n");
        set("unit", "捧");
        set("life", 3);
        set("value", 0);
        set("fruit_remaining", 5); 
        set("food_supply", 10);   
        set("water_supply", 40);  
        //每次吃的msg,沒有也可以的。
        set("eat_msg", "$N拿起$n，剝了皮，往嘴裡丟了一顆，“噗”地吐出核。\n"); 
        //最後一口的msg，沒有亦可
        set("end_msg", "$N吃光了最後一顆$n。\n");  
        //吃飽了的msg, 沒有亦可，但不能有代詞。
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        set("gifts", ([
                "per" : 1,
                "int" : 1,
                "spi" : 1,
        ]));
        setup();
}
