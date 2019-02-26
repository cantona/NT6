// xianggua.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(HIG"香瓜"NOR, ({"xiang gua", "xianggua"}));
        set_weight(4000);
        set("long", "一個淡綠色的大香瓜，惹人喜愛。\n");
        set("unit", "個");
        set("value", 0);
        set("life", 15);
        set("fruit_remaining", 3); 
        set("food_supply", 6);   
        set("water_supply", 24);  
        //每次吃的msg,沒有也可以的。
        set("eat_msg", "$N拿起$n，大大的咬了一口。\n"); 
        //最後一口的msg，沒有亦可
        set("end_msg", "$N把剩下的$n吃了個乾淨。\n");  
        //吃飽了的msg, 沒有亦可，但不能有代詞。
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        set("gifts", ([
                "con" : 1,
                "per" : 1,
        ]));
        setup();
}
