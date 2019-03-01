// axe.c

#include <weapon.h>
inherit AXE;

void create()
{
        set_name("喪門斧", ({ "sangmen fu" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("long", "這是一柄喪門斧。\n");
                set("value", 1500);
                set("rigidity",100);
                set("material", "steel");
                set("wield_msg", "$N掣出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n反別腰後。\n");
        }
          init_axe(15);
        setup();
}
