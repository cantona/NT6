// changqiang.c 長槍

#include <weapon.h>
inherit SPEAR;

void create()
{
        set_name("長槍", ({ "chang qiang","qiang","changqiang" }) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "杆");
                set("long", "這是一杆比武專用的的精鋼長槍,威力非比尋常.\n");
                set("value", 0);
                set("material", "iron");
                set("long", "一杆長槍。\n");
                set("wield_msg", "$N抄起一杆$n，順手抖了個槍花。\n");
                set("unwield_msg", "$N哼了一聲，將$n插回後腰。\n");
        }
        init_spear(100);
        setup();
}