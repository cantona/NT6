// mudao.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>

inherit BLADE;

void create()
{
        set_name("木刀", ({"mu dao","mudao", "dao", "blade"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 100);
                set("material", "wood");
                set("long", "這是一木制的單刀，是練武時用的．\n");
                set("wield_msg", "$N抽出一把$n握在手中。\n");
                set("unequip_msg", "$N將手中的$n插入腰後．\n");
        }
        init_blade(5);
        setup();
}
