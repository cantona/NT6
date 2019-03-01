//Cracked by Kafei
// zhuxiao.c

#include <ansi.h>
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("竹簫",({ "zhu xiao", "xiao" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 100);
                set("material", "bamboo");
                set("shape", "flute");
                set("long", "這是一柄三尺來長，精工制成的青竹簫。\n");
                set("wield_msg", "$N拿出一把$n，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_sword(7);
        setup();
}

#include "flute.h"
#include "music.h"