//changjian.c 

#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("長劍", ({"sword", "changjian", "jian", "sword"}));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "柄");
                set("long", "這是一柄長長的精鋼劍，劍口鋒利無比。\n");
                set("value", 400);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }

        init_sword(25);
        setup();
}