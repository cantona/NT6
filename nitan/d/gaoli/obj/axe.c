// 斧子.

#include <weapon.h>
inherit AXE;

void create()
{
        set_name("斧子", ({ "axe"}));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄斧頭。\n");
                set("value", 1500);
                
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回後背。\n");
        }
        init_axe(150);
        setup();
}