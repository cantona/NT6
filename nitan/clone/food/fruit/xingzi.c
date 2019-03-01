// xingzi.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(YEL"杏子"NOR, ({"xing zi", "xingzi","apricot"}));
        set_weight(4000);
        set("long", "一個黃澄澄的大杏子。\n");
        set("unit", "個");
        set("life", 4);
        set("value", 0);
        set("fruit_remaining", 1); //可以吃6口
        set("food_supply", 5);   //每口加10的food
        set("water_supply", 15);  //每口可以加10的water
        set("eat_msg", "$N拿起$n，大大的啃了一口。\n"); 
        set("end_msg", "$N一口就吃掉了這個$n。\n");  
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        set("core", "杏核");         //name
        set("core_id", ({"xing hu", "apricot core", "core", "hu"}) ); //id
        set("core_unit", "個");        //unit
        set("core_long", "一個啃得幹幹凈凈的杏核。\n"); //long
        set("gifts", ([
                "int" : 1,
        ]));
        setup();
}
