// mupa.c 
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit RAKE;

void create()
{
        set_name("木耙", ({"mu pa", "pa", "rake"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 100);
                set("material", "wood");
                set("long", "這是一柄長長的木耙，是練武時用的．\n");
                set("wield_msg", "$N抽出一柄$n握在手中。\n");
        }
        init_rake(15);
        setup();
}
