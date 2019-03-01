// toujin.c
// Last Modifyed by Ahda on Jan. 4 2002
 
#include <armor.h>
 
inherit HEAD;
 
void create()
{
        set_name("頭巾", ({ "tou jin" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "steel");
                set("unit", "條");
                set("long", "這是一條頭巾，用以纏繞頭部。\n");
                set("value", 1500);
                set("armor_prop/dodge", -5);
        }
        setup();
}