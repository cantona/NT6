// axe.c 板斧

#include <weapon.h>
inherit AXE;

void create()
{
        set_name("板斧", ({ "ban fu", "axe", "fu" }));
        set_weight(50000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄沉重的板斧。\n");
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N「忽」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰後。\n");
        }
        init_axe(25);
        setup();
}