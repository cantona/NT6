// ttoujin.c
 
#include <armor.h>
 
inherit HEAD;
 
void create()
{
        set_name("台夷頭巾", ({ "tou jin" }) );
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "條");
                set("long", "這是一條台夷頭巾，用以纏繞頭部。\n");
                set("value", 1500);
                set("armor_prop/dodge", -5);
        }
        setup();
}