// baodi_kuaixue.c

#include <armor.h>
inherit BOOTS;
void create()
{
        set_name("薄底快靴", ({"baodi kuaixue", "xue", "shoes"}));
        set_weight(500);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "這雙靴子縫製精細，輕便靈巧，武林人士常傳這種靴子。\n");
                set("unit", "雙");
                set("value", 200);
                set("material", "silk");
                set("armor_prop/armor", 1);
                set("armor_prop/dodge", 10);
        }
        setup();
}