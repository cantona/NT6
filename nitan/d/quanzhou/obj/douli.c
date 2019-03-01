// douli.c
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit HEAD;

void create()
{
        set_name("須鯜", ({ "dou li", "douli" }) );
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "階");
                set("material", "cloth");
                set("value", 150);
                set("armor_prop/armor", 2);
        }
        setup();
}
