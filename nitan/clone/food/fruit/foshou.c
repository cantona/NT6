// foshou.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(YEL"佛手"NOR, ({"fo shou", "foshou" }));
        set_weight(4000);
        set("long", "一個嬌黃的佛手。\n");
        set("unit", "個");
        set("life", 7);
        set("value", 0);
        set("fruit_remaining", 2); //可以吃5口
        set("food_supply", 15);   //每口加5的food
        set("water_supply", 25);  //每口可以加15的water
        set("eat_msg", "$N拿起$n，大大的啃了一口。\n");
        set("end_msg", "$N仔細的啃完了這個$n。\n");
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n");
        set("gifts", ([
                "per" : 2,
        ]));
        setup();
}