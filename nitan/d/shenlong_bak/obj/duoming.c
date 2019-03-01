// duoming.c  奪命劍
// Last Modified by winder on Jul. 12 2002

#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("奪命劍", ({ "duoming jian", "jian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄輕巧的精鋼劍，鋒利無比，女劍客們都喜歡配帶此劍。\n");
                set("value", 1000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(30);
        setup();
}