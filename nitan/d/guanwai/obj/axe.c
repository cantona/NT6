// axe.c

#include <weapon.h>

inherit AXE;

void create()
{
        set_name("斧頭", ({ "axe", "fu tou" }));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把斧頭，頗為沉重，是伐樹的好工具。\n");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N抓起一把斧頭，握在手中。\n");
                set("unwield_msg", "$N將手中的斧頭收了回來。\n");
        }
        init_axe(30, TWO_HANDED);
        setup();
}