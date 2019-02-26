// laiyangli.c

#include <ansi.h>

inherit ITEM;
inherit F_FRUIT;


void create()
{
        set_name(HIY"萊陽梨"NOR, ({"laiyang li","li","pear"}));
        set_weight(4000);
        set("long", "一個大大的脆生生黃澄澄的萊陽產的鴨梨。\n");
        set("unit", "個");
        set("life", 7);
        set("value", 0);
        set("fruit_remaining", 2); //可以吃5口
        set("food_supply", 15);   //每口加5的food
        set("water_supply", 25);  //每口可以加15的water
        set("eat_msg", "$N拿起$n，大大的啃了一口。\n");
        set("end_msg", "$N仔細的啃完了這個$n。\n");
        set("over_msg", "吃這麼多？小心撐破肚皮！！！！\n");
        set("core", "梨核");         //name
        set("core_id", ({"li hu", "pear core", "hu", "core"}) ); //id
        set("core_unit", "個");        //unit
        set("core_long", "一個啃得乾乾淨淨的梨核。\n"); //long
        set("gifts", ([
                "per" : 2,
                "int" : 2,
                "con" : -1,
        ]));
        setup();
}