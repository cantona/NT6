#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "頭盔之魂" NOR, ({"head soul1", "head", "soul1"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "這是一個頭盔之魂。\n" NOR);
                set("unit", "個");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "head");
        set("status", 1);
        set("auto_load", 1);
        
        setup();
}

