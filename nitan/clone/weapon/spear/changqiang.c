// changqiang.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit SPEAR;

void create()
{
        set_name("長槍", ({ "chang qiang","qiang","changqiang" }) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("value", 1000);
                set("material", "wood");
                set("long", "一桿長槍。\n");
                set("wield_msg", "$N抄起一桿$n，順手抖了個槍花。\n");
//                set("unwield_msg", "$N哼了一聲，將$n插回後腰。\n");
        }
        init_spear(30);
        setup();
}