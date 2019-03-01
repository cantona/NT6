#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;


void create()
{
        set_name(YEL "葫蘆" NOR, ({"hu lu","pot","hu"}));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一個用來裝水的大葫蘆，外皮金黃，裡面能裝好幾斤清水。\n");
                set("unit", "個");
                set("value",3);
                set("max_liquid", 10);
        }
        set("liquid", ([
                "type": "water",
                "name": "清水",
                "remaining": 10,
                "drunk_apply": 30,
        ]));
}
