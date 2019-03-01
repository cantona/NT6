// damao.c

#include <armor.h>
inherit HEAD;
void create()
{
        set_name("范陽氈大帽", ({ "da mao", "head" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "頂");
                set("value",500);
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
}