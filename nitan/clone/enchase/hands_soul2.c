#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "鐵掌之魂" NOR, ({"hands soul2", "hands", "soul2"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "這是一個鐵掌之魂。\n" NOR);
                set("unit", "個");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "hands");
        set("status", 2);
        set("auto_load", 1);
        
        setup();
}

