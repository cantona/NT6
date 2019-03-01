// apple.c
#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;

void create()
{
        set_name(HIR"蘋果"NOR, ({"ping guo","pingguo","apple"}));
        set_weight(4000);
        set("long", "一個又大又紅，圓鼓鼓的大蘋果。\n");
        set("unit", "個");
        set("life", 7);
        set("value", 0);
        set("fruit_remaining", 4); //可以吃4口
        set("food_supply", 15);   //每口加15的food
        set("water_supply", 4);  //每口可以加4的water
        //每次吃的msg,沒有也可以的。
        set("eat_msg", "$N拿起$n，大大的咬了一口。\n"); 
        //最後一口的msg，沒有亦可
        set("end_msg", "$N三口兩口吃完了這個$n。\n");  
        //吃飽了的msg, 沒有亦可，但不能有代詞。
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        // 水果吃完剩下的東西 :-)
        set("core", "蘋果核");         //name
        set("core_id", ({"pingguo hu", "apple core", "hu", "core"}) ); //id
        set("core_unit", "個");        //unit
        set("core_long", "一個蘋果核。\n"); //long
        set("gifts", ([
                "int" : 1,
                "spi" : 1,
                "per" : 1,
        ]));
        setup();
}
