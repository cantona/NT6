// ruanjian.c 軟劍

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("軟劍", ({ "ruanjian", "jian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄用特殊材料製成的鋼劍。\n");
                set("value", 150);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(35);
        setup();
}
