#include <weapon.h>
inherit STAFF; 
void create()
{
        set_name("細竹竿", ({ "bamboo", "zhu gan" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "一根通體碧綠的竹竿。\n");
                set("value", 100);
                set("rigidity", 5);
                set("material", "wood");
                set("wield_msg", "$N拿出一根通體碧綠的$n握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
    }
    ::init_staff(5);
}        
