// wolfarrow.c
 
#include <weapon.h>
 
inherit THROWING;

int is_arrow() { return 1; }
 
void create()
{
        set_name("狼牙箭", ({ "arrow", "jian" }));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一根細長的箭，簇失略彎，如同狼牙一般陰森森的。\n");
                set("unit", "把");
                set("base_unit", "根");
                set("base_weight", 150);
                set("base_value", 500);
                set("wound_percent", 90);
        }

        set_amount(1);
        init_throwing(300);
        setup();

        set("no_wield", "這不是用來裝備的。\n");
}