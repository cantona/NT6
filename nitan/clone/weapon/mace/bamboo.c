//bamboo.c
//created 5-30-97 pickle

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
        set_name("短竹", ({"bamboo piece", "mace", "bamboo", "piece"}));
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 100);
                set("material", "wood");
                set("long", "一根短竹，大概是因為浸過水的原故拿在手裏沉甸甸的。\n");
                set("wield_msg", "$N操起一根$n，擺了個架式。\n");
                set("unwield_msg", "$N將$n別回腰間。\n");
        }
        
        init_mace(5);
        setup();
}
