// arrow.c
 
#include <weapon.h>
 
inherit THROWING;

int is_arrow() { return 1; }
 
void create()
{
        set_name("羽箭", ({ "arrow", "jian" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一根細長的箭，箭翎修長，簇失鋒利。\n");
                set("unit", "把");
                set("base_unit", "根");
                set("base_weight", 100);
                set("base_value", 200);
                set("wound_percent", 80);
        }

        set_amount(1);
        init_throwing(200);
        setup();

        set("no_wield", "這不是用來裝備的。\n");
}