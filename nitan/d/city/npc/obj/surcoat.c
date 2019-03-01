// necklace.c 肚帶
 
#include <armor.h>
 
inherit SURCOAT;
 
void create()
{
        set_name("肚帶", ({ "surcoat", "du dai", "dai" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "leather");
                set("unit", "條");
                set("long", "這是一件皮質的肚帶，用以保護腹部。\n");
                set("value", 800);
                set("armor_prop/dodge", -3);
        }
        setup();
}