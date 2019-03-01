#include <ansi.h>

inherit EQUIP_SOUL;

void create()
{
        set_name(HIM "護身符之魂" NOR, ({"charm soul3", "charm", "soul3"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "這是一個護身符之魂。\n" NOR);
                set("unit", "個");
                set("value", 200000);
                set("no_sell", 1);
        }
        set("type", "charm");
        set("status", 3);
        set("auto_load", 1);
        
        setup();
}

