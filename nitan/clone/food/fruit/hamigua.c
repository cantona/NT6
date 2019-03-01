// hamigua.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(HIG"哈蜜瓜"NOR, ({"hami gua", "hamigua","cantaloup"}));
        set_weight(8000);
        set("long", "一塊切好了的哈蜜瓜。\n");
        set("unit", "塊");
        set("life", 2);
//        set("value", 800);//因為是從外國運了幾個月才運到的。
        set("fruit_remaining", 3); //可以吃5口
        set("food_supply", 30);   //每口加5的food
        set("water_supply", 70);  //每口可以加5的water
        //每次吃的msg,沒有也可以的。
        set("eat_msg", "$N拿起$n，大大的咬了一口，真甜啊～～\n");
        //最後一口的msg，沒有亦可
        set("end_msg", "$N啃完了$n。\n");  
        //吃飽了的msg, 沒有亦可，但不能有代詞。
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        // 水果吃完剩下的東西 :-)
        set("core", "哈蜜瓜皮");         //name
        set("core_id", ({"hamigua pi", "pi", "peel"}) ); //id
        set("core_unit", "塊");        //unit
        set("core_long", "一塊哈蜜瓜皮。\n"); //long
        set("gifts", ([
                "int" : 1,
                "con" : 1,
        ]));
        setup();
}
