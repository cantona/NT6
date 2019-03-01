// longsword.c 長劍

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("長劍", ({ "changjian", "jian" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄普通的精鋼劍，一般的劍客都配帶此劍。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(25);
        setup();
}