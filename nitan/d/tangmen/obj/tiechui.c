// hammer.c

#include <weapon.h>
#include <ansi.h>
inherit HAMMER;

void create()
{
        set_name("鐵錘", ({ "hammer" }) );
        set_weight(25000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把沈重的鐵錘，打造的相當堅實。\n");
                set("value", 300);
                set("rigidity",160);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，試了試重量，然後握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_hammer(1);
        setup();
}