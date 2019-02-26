#include <weapon.h>
inherit AXE;

void create()
{
        set_name("鏽鐵斧", ({ "xiu tiefu", "axe" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄精鋼打造的斧頭。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", 
"$N「唰」的一聲拔出一柄精光閃閃的斧頭握在手裏。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_axe(20);
        setup();
}
