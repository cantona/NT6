// muchui.c 木錘

#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name("木錘", ({ "hammer" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                        set("long", "一根削得很精緻的短錘。\n");
                set("value", 3);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，試了試重量，然後握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_hammer(2);
        setup();
}