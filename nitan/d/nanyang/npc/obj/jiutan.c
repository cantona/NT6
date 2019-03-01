// Room: /d/nanyang/npc/obj/jiutan.c
// Last Modified by winder on Nov. 20 2001

inherit ITEM;
#include <ansi.h>
inherit F_LIQUID;
void create()
{
        set_name(YEL "黃酒壇子" NOR, ({"jiu tanzi", "tanzi", "pot"}));
        set_weight(8000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝黃酒的大泥壇子，封口上貼著紅紙。\n");
                set("unit", "個");
                set("value", 800);
                set("max_liquid", 120);
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