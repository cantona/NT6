// bahammer.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name("八寶銅錘", ({ "hammer" }) );
        set_weight(10000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","這是一把沉重的銅錘，打造的相當堅實。沒有千斤力氣是拿不起的。\n");
                set("value", 1200);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，試了試重量，然後握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_hammer(35);
        setup();
}
