// shortsword.c 長劍

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("短劍", ({ "duanjian", "jian" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄劍身短小的精鋼劍，一般的劍客都配帶此劍。\n");
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(15);
        setup();
}