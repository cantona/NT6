// rustsword.c

#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(RED"長劍"NOR, ({ "rustsword" }));
        set_weight(6000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄鏽跡斑斑的鋼劍，不過似乎隱藏著一些光芒。\n");
                set("value", 400000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(10);
        setup();
}