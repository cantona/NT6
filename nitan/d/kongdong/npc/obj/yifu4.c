#include <armor.h>
inherit CLOTH;


void create()
{
        set_name("紫袍子", ({ "cloth" }) );
        set("long","一件穿了多年的袍子，漿洗得十分乾淨。\n");
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
              
                set("armor_prop/armor", 1);
        }
        setup();
}
