#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name(YEL "酒葫蘆" NOR, ({ "jiu hulu", "hulu", "jiu" }));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝酒的大葫蘆，外皮金黃，裡面能裝好幾斤酒。\n");
                set("unit", "個");
                set("value", 100);
                set("max_liquid", 15);
        }
        set("liquid", ([
                "type": "alcohol",
                "name": "米酒",
                "remaining": 15,
                "drunk_apply": 3,
        ]));
}