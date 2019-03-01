// xigua.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(GRN"西瓜"NOR, ({"xi gua", "xigua","watermelon"}));
        set_weight(8000);
        set("long", "一塊切好了的西瓜，黑籽紅瓤，嘿～～快吃吧！\n");
        set("unit", "塊");
        set("value", 0);
        set("fruit_remaining", 2); //可以吃5口
        set("food_supply", 13);   //每口加5的food
        set("water_supply", 27);  //每口可以加5的water
        //每次吃的msg,沒有也可以的。
        set("eat_msg", "$N拿起$n，大大的咬了一口，爽啊～～\n");
        //最後一口的msg，沒有亦可
        set("end_msg", "$N啃完了$n，“噗噗噗”吐出一堆西瓜籽來。\n");  
        //吃飽了的msg, 沒有亦可，但不能有代詞。
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        // 水果吃完剩下的東西 :-)
        set("core", "西瓜皮");         //name
        set("core_id", ({"xigua pi", "pi", "peel"}) ); //id
        set("core_unit", "塊");        //unit
        set("core_long", "一塊西瓜皮。\n"); //long
        set("gifts", ([
                "per" : 1,
                "spi" : 1,
        ]));
        setup();
}
