// toukui.c 頭盔
 
#include <armor.h>
 
inherit HEAD;
 
void create()
{
        set_name("頭盔", ({ "helmet", "toukui" }) );
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "頂");
                set("long", "這是一頂鐵質的肚帶，用以保護頭部。\n");
                set("value", 1500);
                set("armor_prop/dodge", -5);
        }
        setup();
}