// hammer.c
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name( "法輪",({ "fa lun" ,"lun" ,"falun" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long","這是一柄法輪，僧人們用它來作法事。\n");
                set("material", "wood");
                set("wield_msg", "$N抽出一柄$n握在手中。\n");
                set("unwield_msg","$N將手中的$n放回腰間。\n");
        }
        init_hammer(5);
        setup();
}

/*#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name("鐵錘", ({ "hammer" }) );
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把沈重的鐵錘，打造的相當堅實。\n");
                set("value", 3);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，試了試重量，然後握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_hammer(25);
        setup();
}
*/