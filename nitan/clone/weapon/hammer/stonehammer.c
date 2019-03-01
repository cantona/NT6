// stonehammer.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name("石鎖", ({"stone hammer","stone", "hammer"}));
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一把沉重的石鎖。\n");
        }
        init_hammer(25);
        setup();
}
