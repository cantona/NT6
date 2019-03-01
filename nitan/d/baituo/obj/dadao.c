#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("大刀", ({ "da dao", "da", "dao" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 200);
                set("material", "iron");
                set("long", "這是一柄鐵打的大刀。\n");
                set("wield_msg", "$N抽出一把$n握在手中。\n");
                set("unequip_msg", "$N將手中的$n插回腰間。\n");
        }
        init_blade(10);
        setup();
}