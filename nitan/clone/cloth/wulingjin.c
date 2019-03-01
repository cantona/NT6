// wulingjin.c 
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit HEAD;

void create()
{
        set_name("烏綾巾", ({ "wuling jin", "jin" }) );
        set_weight(700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "頂");
                set("long", "一頂黑緞子制成的絲帶，用來束發。\n");
                set("value", 300);
                set("material", "cloth");
                set("armor_prop/armor", 1);
                set("armor_prop/per", 1);
        }
        setup();
}
