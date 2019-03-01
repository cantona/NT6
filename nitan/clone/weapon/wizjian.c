// wizjian.c 御用劍

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("御用劍", ({ "wizard sword", "sword", "jian" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄神仙用的御用劍，通體散發著金色的光芒。\n");
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(1000);
        setup();
}