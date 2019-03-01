// bishou.c 匕首
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit SWORD;
inherit F_UNIQUE;

void create()
{
        set_name(HIR "匕首" NOR, ({ "bishou","sword" }));
        set_weight(20000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "細看那匕首，劍身如墨，無半點光澤。\n");
                set("value", 50000);
                set("material", "steel");
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_give", "這樣東西不能給人。\n");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中，只覺一股寒氣撲面而來。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘，只聽“嗤”的一聲輕響。\n");
        }
        init_sword(150);
        setup();
}