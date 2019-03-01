// Last Modified by Winder on May. 25 2001
// fangbianchan.c

#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("方便鏟", ({ "fangbianchan","fangbian", "chan" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "條");
                set("value", 5);
                set("material", "wood");
                set("long", "一條非常粗大結實的方便鏟。\n");
                set("wield_msg", "$N拿起一根$n，在手中掂量掂量。\n");
                set("unwield_msg", "$N哼了一聲，將$n放回身後。\n");
        }
        init_staff(35);
        setup();
}