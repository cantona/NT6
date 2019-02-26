// hongzao.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(RED"紅棗"NOR, ({"hong zao", "hongzao"}));
        set_weight(4000);
        set("long", "一把紅紅的大棗。\n");
        set("unit", "把");
        set("value", 0);
        set("fruit_remaining", 18); 
        set("food_supply", 2);   
        set("water_supply", 1);  
        set("eat_msg", "$N拿起$n，丟了一顆到嘴裏，“噗”的一聲吐出棗核。\n"); 
        set("end_msg", "$N把剩下的$n吃了個乾淨。\n");  
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n"); 
        setup();
}
