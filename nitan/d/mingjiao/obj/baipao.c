// baipao.c
//

#include <armor.h>

inherit CLOTH;

void create()
{
        set_name("白布長袍", ({ "cloth","pao" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "件");
                set("long", 
                        "這是件白布長袍，雖不奢華，卻洗得一塵不染，在袍襟上鏽了一團血紅的火燄，\n"
                        "頗為鮮艷。\n");
                set("material", "cloth");
                set("armor_prop/armor", 1);
        }
        setup();
}
