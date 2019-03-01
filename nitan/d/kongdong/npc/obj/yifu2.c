#include <armor.h>
inherit CLOTH;


void create()
{
        set_name("紫綢長衫", ({ "cloth" }) );
        set("long","一件紫色的綢面長衫，穿起來很氣派。\n");
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "cloth");
                set("value",1000);
                set("armor_prop/armor", 1);
        }
        setup();
}
