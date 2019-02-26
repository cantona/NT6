// jueqingwhip.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit F_UNIQUE;
inherit WHIP;

void create()
{
        set_name("情絲", ({"silk whip", "whip"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一條藍色的長帶，細看由無數細如毛髮的長絲聚成，雖輕若無物，卻無孔不入。\n");
                set("unit", "條");
                set("value", 12000);
                set("wield_msg", "$N左手輕揚，一條藍色綢帶忽地甩了出來。\n");
                set("unwield_msg", "$N把手中$n纏回腰間。\n");
                set("weapon_prop/courage", 5);
        }
        init_whip(60);
        set("is_monitored",1);
        setup();
}
