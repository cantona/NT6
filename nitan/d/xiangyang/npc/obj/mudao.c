// mudao.c

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("木刀", ({ "mu dao", "blade", "dao" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄木匠做的木刀，手工相當精細。\n");
                set("value", 50);
                set("material", "steel");
                set("wield_msg", "$N從腰帶裏抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰帶上。\n");
        }
        init_blade(3);
        setup();
}