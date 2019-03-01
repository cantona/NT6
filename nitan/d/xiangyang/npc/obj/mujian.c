// mujian.c

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("木劍", ({ "mu jian", "sword", "jian" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄木匠做的木劍，手工相當精細。\n");
                set("value", 50);
                set("material", "steel");
                set("wield_msg", "$N從腰帶裏抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰帶上。\n");
        }
        init_sword(3);
        setup();
}