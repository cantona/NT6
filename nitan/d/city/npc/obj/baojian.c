// longsword.c 長劍

#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIW"寶劍"NOR, ({"bao jian", "sword" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這似乎是一把不同尋常的劍，刃口鋒利無比。\n");
                set("value", 100);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(25);
        setup();
}