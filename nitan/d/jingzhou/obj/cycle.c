// necklace.c 武者項圈
 
#include <armor.h>
 
inherit NECK;
 
void create()
{
        set_name("武者項圈", ({ "neck-cycle", "xiang quan", "lian" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "串");
                set("long", "這是一串鐵質的項鏈，用以保護頸部。\n");
                set("value", 1800);
                set("armor_prop/dodge", 5);
        }
        setup();
}