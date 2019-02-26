#include "herb.h"

void create()
{
        set_name(HIC "金絲還陽" NOR, ({ "hy-js", "herb_hy_js" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "金髮繭科植物高山金髮蘚的全草。因其植物體早黃棕色，形如金絲，故得此名。。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

