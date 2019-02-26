// cloth: wcloth.c
// Jay 3/17/96

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("羊皮襖", ({ "yangpi ao", "ao"}) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", "這是一件灰色的羊皮襖。牧羊人不管春夏秋冬, 颳風下雨都穿着它。\n");
                set("material", "cloth");
                set("armor_prop/armor", 3);
                set("warm_cloth", 1);
                set("value", 500);
        }
        setup();
}
