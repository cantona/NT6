#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "項鏈之魂" NOR, ({"neck soul6", "neck", "soul6"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "這是一個項鏈之魂。\n" NOR);
                set("unit", "個");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "neck");
        set("status", 6);
        set("auto_load", 1);
        
        setup();
}

