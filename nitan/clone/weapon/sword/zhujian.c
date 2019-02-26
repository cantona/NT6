// zhujian.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name("竹劍",({ "zhu jian","zhujian", "jian", "sword" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 100);
                set("material", "bamboo");
                set("long","這是一柄三尺來長，精工製成的青竹劍，雖不致命，卻可傷人。\n");
                set("wield_msg", "$N拿出一把$n，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_sword(10);
        setup();
}