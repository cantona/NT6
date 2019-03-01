// cloth: wcloth.c
// Jay 3/17/96

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("維吾爾族長袍", ({ "weiwuer robe", "robe"}) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", "這是一件色彩斑斕的維吾爾族長袍\n");
                set("material", "cloth");
                set("armor_prop/armor", 2);
                set("value", 50);
        }
        setup();
}
