// snow_sword.c 

#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("風回雪舞劍", ({ "snowsword", "xue jian", "sword" }) );
        set_weight(400);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 700);
                set("material", "steel");
                set("long", "這是一把用來練舞的劍，劍身細長，輕巧尤鋒利。\n");
                set("wield_msg", "$N抽出一把劍身細長的劍，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
                set("weapon_prop/courage", 4);
        }
        init_sword(40);
        setup();
}
