// yangmei.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(RED"楊梅"NOR, ({"yang mei", "yangmei", "redbayberry"}));
        set_weight(4000);
        set("long", "一捧紅豔豔的楊梅。\n");
        set("unit", "捧");
        set("value", 0);
        set("life", 3);
        set("fruit_remaining", 8); 
        set("food_supply", 1);   
        set("water_supply", 4);  
        set("eat_msg", "$N拿起$n，往嘴裏丟了一顆，“噗”地吐出核。\n"); 
        set("end_msg", "$N吃光了最後一顆$n，卻覺得牙有點酸。\n");  
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n");
/* 
        set("gifts", ([
                "per" : 1,
                "int" : 1,
                "spi" : 1,
        ]));
*/
        setup();
}
