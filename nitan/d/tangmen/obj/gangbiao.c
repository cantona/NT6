// gangbiao.c
#include <weapon.h>
inherit THROWING;

void create()
{
        set_name("鋼鏢", ({"gangbiao", "biao" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這是一把普通的鋼鏢。\n");
                set("unit", "些");
                set("base_value", 1);
                set("material", "steel");
                set("base_unit", "枚");
                set("base_weight", 10);
        }
        set_amount(1);
        init_throwing(25);
        setup();
}
