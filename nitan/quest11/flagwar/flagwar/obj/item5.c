#include <ansi.h>

inherit ITEM; 

void create()
{
	      set_name(HIG"搶旗戰 - "HIW"驚雷符"NOR, ({"fwar count seal","seal"}) );
        set_weight(300);
        set("unit", "個");
        set("long", "搶旗戰專用特殊物品，放在身上在死亡時會自動使用。\n");
        set("value", 1);
        set("no_store",1);
        set("no_sell", 1);
        set("flag_war_item", 1);
 //       set("no_get", 1);
        set("no_drop", 1);
        setup();
}