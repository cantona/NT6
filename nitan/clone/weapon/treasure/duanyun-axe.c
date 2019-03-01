// duanyun-axe.c 斷雲斧
// Last Modified by suncity on Feb. 13 2003

#include <ansi.h>;
#include <weapon.h>;
inherit AXE;
inherit F_UNIQUE;

void create()
{
        set_name(HIW"斷雲斧"NOR, ({ "duanyun fu", "axe", "fu" }) );
        set_weight(40000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 10000);
                set("material", "iron");
                set("long", HIW"這是一把銀光閃閃的斧頭。\n"NOR );
                set("wield_msg", HIW"一道白光，$n已在$N手中，只覺氣成風雲，聲為雷霆。\n"NOR);
                set("unwield_msg", HIW"$N放下手中的$n，華光頓斂，天地間只聞龍鳴。\n"NOR);
        }
        init_axe(250);
        setup();
}