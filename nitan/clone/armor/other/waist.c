// waist.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit WAIST;

void create()
{
        set_name("腰帶", ({"waist"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "leather");
                set("unit", "條");
                set("armor_prop/armor", 1);
        }
        setup();
}
