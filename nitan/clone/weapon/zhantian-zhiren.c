// longsword.c 長劍

#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIR "斬天之刃" NOR, ({ "zhantian zhiren", "zhantian", "zhiren" }));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIR "傳說斬天之刃可以開天辟地，破氣穿甲，無所不能。\n" NOR);
                set("value", 2000);
                set("material", "tian jing");
                set("wield_msg", HIR "「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(1000);
        setup();
}
