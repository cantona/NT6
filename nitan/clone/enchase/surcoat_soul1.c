#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "披風之魂" NOR, ({"surcoat soul1", "surcoat", "soul1"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "這是一個披風之魂。\n" NOR);
                set("unit", "個");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "surcoat");
        set("status", 1);
        set("auto_load", 1);
        
        setup();
}

