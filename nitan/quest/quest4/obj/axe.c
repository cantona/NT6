#include <weapon.h>
inherit AXE;
void create()
{
        set_name("大板斧", ({ "bigaxe", "axe" }) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("material", "steel");
                set("long", "這是一把沉重的大板斧，砍起東西來非常順手。\n");
                set("value", 500);
                set("rigidity", 150); 
                set("wield_msg", "$N拿出一把$n，握在手中當作武器。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_axe(40, TWO_HANDED);
        setup();
}
