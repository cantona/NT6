// mudao.c

#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name("木魚槌", ({ "muyu chui", "chui" }) );
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 50);
                set("material", "wood");
                set("long", "這是一把和尚念經俏木魚用的小木槌。\n");
                set("wield_msg", "$N從衣袋裡掏出一根$n，握在手中當武器。\n");
                set("unequip_msg", "$N將手中的$n放回衣袋。\n");
                set("shaolin",1);
        }
        init_hammer(1);
        setup();
}