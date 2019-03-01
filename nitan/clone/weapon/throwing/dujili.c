// dujili.c 
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit THROWING;

void create()
{
        set_name("毒蒺黎", ({"poison dart", "dart"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("base_unit", "枝");
                set("long","鐵打的蒺黎鋒利無比，刃上閃現綠色，顯是喂了毒藥。\n");
                set("base_weight", 40);
                set("value", 0);
                set("base_value", 5);
        }
        set_amount(20);
        init_throwing(15);
        setup();
}
