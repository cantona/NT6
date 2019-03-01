// musword.c 木劍

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("木劍", ({ "woodjian", "jian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄練功用的木劍，劍頭是平的。\n");
                set("value", 100);
                set("material", "wood");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(5);
        setup();
}