// boots.c 皮靴
 
#include <armor.h>
 
inherit BOOTS;
 
void create()
{
        set_name("皮靴", ({ "boots", "pi xue", "xue" }) );
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "leather");
                set("unit", "雙");
                set("long", "這是一雙用上好牛皮作的皮靴，據說由上海進口。用以保護足部。\n");
                set("value", 1000);
                set("armor_prop/dodge", 8);
        }
        setup();
}