// lizi.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(MAG"李子"NOR, ({"li zi", "lizi","plum"}));
        set_weight(4000);
        set("long", "一個圓溜溜的大李子。\n");
        set("unit", "個");
        set("value", 0);
        set("fruit_remaining", 1); //可以吃6口
        set("food_supply", 5);   //每口加10的food
        set("water_supply", 25);  //每口可以加10的water
        //每次吃的msg,沒有也可以的。
        set("eat_msg", "$N拿起$n，大大的啃了一口。\n"); 
        //最後一口的msg，沒有亦可
        set("end_msg", "$N仔細的啃完了這個$n。\n");  
        //吃飽了的msg, 沒有亦可，但不能有代詞。
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        // 水果吃完剩下的東西 :-)
        set("core", "李子核");         //name
        set("core_id", ({"lizi hu", "plum core", "core", "hu"}) ); //id
        set("core_unit", "個");        //unit
        set("core_long", "一個啃得乾乾淨淨的李子核。\n"); //long
        setup();
}
