// nuanmao.c

#include <armor.h>
inherit HEAD;
void create()
{
        set_name("殑鳥轡簽", ({ "nuan mao", "head" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "階");
                set("value",150);
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}