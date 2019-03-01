// tiejian.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("鐵劍", ({"sword"}));
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一把鏽跡駁駁的鐵劍，但相當的鋒利。\n");
                set("unit", "把");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(30);
        setup();
}
