#include <armor.h>
inherit HEAD;

void create()
{
        set_name( "束髮金帶" , ({ "jindai" }) );
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "條");
                set("value", 1500);
                set("material", "silk");
                set("armor_prop/armor", 1);
        set("wear_msg", "$N將$n拿出束在頭髮上。\n");
        }
        setup();
}