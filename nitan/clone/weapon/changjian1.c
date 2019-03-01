// longsword.c 長劍

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("長劍", ({ "long sword", "sword", "jian" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄比武專用的的精鋼劍,威力非比尋常.\n");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(100);
        setup();
}