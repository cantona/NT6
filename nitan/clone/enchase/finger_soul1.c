#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "指套之魂" NOR, ({"finger soul1", "finger", "soul1"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "這是一個指套之魂。\n" NOR);
                set("unit", "個");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "finger");
        set("status", 1);
        set("auto_load", 1);
        
        setup();
}

