// gangbiao.c
#include <weapon.h>
inherit THROWING;

void create()
{
        set_name("子母回魂鏢", ({"hhbiao", "biao" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一把唐門特制的鋼鏢，威力無窮。\n");
                set("unit", "些");
                set("base_value", 1);
                set("material", "steel");
                set("base_unit", "枚");
                set("base_weight", 10);
        }
        set_amount(1);
        init_throwing(100);
        setup();
}
