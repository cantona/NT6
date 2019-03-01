// tiepipa.c

#include <weapon.h>
#include <ansi.h>
inherit HAMMER;

void create()
{
        set_name(HIB"鐵琵琶"NOR, ({ "tiepipa" }) );
        set("taskobj", 1);
        set_weight(50000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把奇形鐵琵琶，打造的相當精巧堅實。\n");
                set("value", 0);
                set("material", "iron");
                set("wield_msg", "$N從背上解下一把$n，然後橫在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        setup();
}