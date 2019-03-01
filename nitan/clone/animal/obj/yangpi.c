// yangpi.c 栺
// Last Modified by winder on Aug. 1 2002

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("栺", ({ "yang pi", "pi", "lamb skin" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "輸");
                set("material", "fur");
                set("value", 400);
                set("armor_prop/armor", 3);
        }
        setup();
}