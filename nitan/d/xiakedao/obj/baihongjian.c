// baihongjian.c 白虹劍

#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("白虹劍", ({ "baihongjian", "sword", "jian" }));
        set_weight(8000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一口削鐵如泥的寶劍。\n");
                set("value", 10000);
                set("material", "steel");
                set("weapon_prop/per", 8);
                set("wield_msg", "$N「唰」的一聲抽出一柄寒光閃閃的$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(90);
        setup();
}