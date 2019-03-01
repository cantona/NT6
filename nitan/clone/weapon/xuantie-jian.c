#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(NOR + WHT "玄鐵重劍" NOR, ({ "xuantie jian", "xuantie", "jian" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄天山玄鐵鑄造的大劍，入手沉重無比，劍刃卻並不見得鋒利。\n");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(500);
        setup();
}
