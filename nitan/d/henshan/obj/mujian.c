#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("木劍", ({ "mu jian","jian" }));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄用樹枝削成的木劍。\n");
                set("value", 50);
                set("material", "wood");
                set("wield_msg", "$N抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(1);
        setup();
}
