// xiangliao.c 香料

#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("特制香料", ({ "xiang liao", "xiangliao", "liao" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一塊特制的香料，點燃後可以發出濃鬱的香氣。\n");
                set("base_unit", "塊");
                set("base_weight", 1);
                set("base_value", 1);
                set("no_sell", 1);
                set("unit", "些");
        }

        set_amount(1);
        setup();
}
