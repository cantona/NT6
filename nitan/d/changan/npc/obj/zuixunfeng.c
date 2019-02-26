//zuixunfeng.c

#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name(MAG"醉薰風"NOR, ({ "zui xunfeng", "xunfeng" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long", "一壺巴蜀佳釀"MAG+"醉薰風"NOR"，甜美醇綿。\n");
                set("unit", "壺");
                set("value", 500);
                set("max_liquid", 10);
        }
        set("liquid", ([
                "type": "alcohol",
                "name": MAG"醉薰風"NOR"佳釀",
                "remaining": 25,
                "drunk_apply": 7,
        ]) );
}