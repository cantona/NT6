// lemon.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
        set_name(HIG"檸檬"NOR, ({"ning meng", "ningmeng", "lemon"}));
        set_weight(4000);
        set("long", "一個黃綠色的檸檬。\n");
        set("unit", "個");
        set("life", 5);
        set("value", 0);
        set("fruit_remaining", 2); 
        set("food_supply", 10);   
        set("water_supply", 40);  
        //每次吃的msg,沒有也可以的。
        set("eat_msg", "$N拿起$n，剝開皮，大大的咬了一口，哇～～酸死了！救命啊！\n"); 
        //最後一口的msg，沒有亦可
        set("end_msg", "$N皺着眉頭吃完了這個$n。\n");  
        //吃飽了的msg, 沒有亦可，但不能有代詞。
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        set("gifts", ([
                "int" : 1,
                "per" : 1,
                "spi" : 1,
        ]));
        setup();
}
