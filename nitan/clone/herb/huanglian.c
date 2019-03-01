#include "herb.h"

void create()
{
        set_name(HIY "黃連" NOR, ({"huang lian"}));

        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("long","黃連：草本植物，味苦，清熱毒。\n");
                set("base_unit", "個");
                set("base_value", 4000);
                set("base_weight", 60);
                set("cure_s",0);
                set("cure_d",20);
                set("cure_n",0);
                
        }
        setup();
}