//ironmace.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
        set_name("鐵鞭", ({"iron mace", "mace", "ironmace"}));
        set_weight(7000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 1000);
                set("material", "iron");
                set("long", "一柄普通的竹節鞭。\n");
                set("wield_msg", "$N操起一根$n，擺了個架式。\n");
                set("unwield_msg", "$N將$n別回腰間。\n");
        }
        
        init_mace(15);
        setup();
}
