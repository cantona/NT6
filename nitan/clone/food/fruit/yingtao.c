// yingtao.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(HIR"櫻桃"NOR, ({"ying tao", "yingtao", "cherry"}));
        set_weight(100);
        set("long", "一捧鮮紅的櫻桃，鮮艷欲滴。\n");
        set("unit", "捧");
//        set("value", 20);
        set("life", 4);
        set("fruit_remaining", 5); 
        set("food_supply", 10);   
        set("water_supply", 10);  
        set("eat_msg", "$N拿起$n，往嘴裡丟了一顆\n"); 
        set("end_msg", "$N吃光了最後一顆$n。\n");  
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        set("gifts", ([
                "spi" : 1,
        ]));
        setup();
}
