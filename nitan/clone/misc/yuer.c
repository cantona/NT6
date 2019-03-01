// yuer.c 魚餌

#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name("魚餌", ({ "yu er", "er" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是釣魚者常用的魚食。\n");
                set("base_unit", "塊");
                set("base_weight", 30);
                set("base_value", 7);
                set("no_sell", "這魚吃的東西你也給我？");
                set("unit", "些");
        }

        set_amount(1);
        setup();
}
