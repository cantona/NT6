#include <weapon.h>
inherit STICK;

void create()
{
        set_name("鑌鐵棍", ({ "bintiegun","tiegun","gun", "bang" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("value", 0);
                set("material", "steel");
                set("long", "一根沉甸甸黑黝黝的鑌鐵棍。\n");
                set("wield_msg", "$N拿起一根$n，順手舞了個棍花。\n");
                set("unwield_msg", "$N哼了一聲，將$n插回後腰。\n");
        }
        init_stick(100);
}                            