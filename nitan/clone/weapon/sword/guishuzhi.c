// Last Modified by winder on May. 25 2001
// guishuzhi.c

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("桂樹枝", ({ "guishuzhi","gui","zhi","jian", "sword" }) );
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("material", "wood");
                set("long", "這是一根細長的桂樹枝。\n");
                set("wield_msg", "$N抽出一根細長的桂樹枝，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
                set("weapon_prop/courage", -4);
        }
        init_sword(6);
        setup();
}