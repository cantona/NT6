// jiuping.c
#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name(GRN"酒瓶"NOR, ({"jiuping", "bottle"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個晶瑩碧綠的的大酒瓶，裝了熏熏醉人的竹葉青。\n");
                set("unit", "個");
                set("value", 1600);
                set("max_liquid", 15);
        }
        set("liquid", ([
                "type": "alcohol",
                "name": "竹葉青",
                "remaining": 15,
                "drunk_apply": 3,
        ]));
}