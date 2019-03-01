
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("鋼劍", ({ "gangjian", "jian","sword" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄官兵用的鋼劍。\n");
                set("value", 1500);
            set("super",2);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回劍鞘。\n");
        }
        init_sword(20,100,100);
        setup();
}