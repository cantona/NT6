// Room: /d/nanyang/npc/obj/jiuhulu.c
// Last Modified by winder on Nov. 20 2001
//這是用來買酒用的葫蘆，不是common裝備用的，所以比較貴。

inherit ITEM;
inherit F_LIQUID;
#include <ansi.h>
void create()
{
        set_name(YEL"酒葫蘆"NOR, ({"jiu hulu", "hulu", "pot"}));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝酒的大葫蘆，外皮金黃，裡面能裝好幾斤酒。\n");
                set("unit", "個");
                set("value", 300);
                set("max_liquid", 30);
        }
        // because a container can contain different liquid
        // we set it to contain wine at the beginning
        set("liquid", ([
                "type": "alcohol",
                "name": "黃酒",
                "remaining": 30,
                "drunk_apply": 10,
        ]));
}
