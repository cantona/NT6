// weapon: /d/xingxiu/npc/obj/yaochu.c
// Last Modified by winder on Feb. 28 2001

#include <weapon.h>

inherit HAMMER;

void create()
{
        set_name("藥鋤", ({ "yaochu", "chu" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把採藥用的藥鋤，已經有些生鏽了。\n");
                set("value", 100);
                set("material", "iron");
                set("wield_msg", "$N拿出一把$n，握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_hammer(5);
        setup();
}