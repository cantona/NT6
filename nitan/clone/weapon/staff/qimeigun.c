// qimeigun.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("齊眉棍", ({ "qimeigun","gun", "bang" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "條");
                set("value", 5);
                set("material", "wood");
                set("long", "一根非常結實的齊眉棍。\n");
                set("wield_msg", "$N拿起一根$n，順手舞了個棍花。\n");
                set("unwield_msg", "$N哼了一聲，將$n插回後腰。\n");
        }
        init_staff(18);
        setup();
}