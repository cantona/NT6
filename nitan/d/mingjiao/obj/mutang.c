//yitianjian.c
#include <weapon.h>

inherit BLADE;

void create()
{
    set_name("木鏜", ({ "mu tang", "mu","tang" }) );
    set_weight(1500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 50);
                set("material", "wood");
                set("long", "這是一把作神道用的木鏜。\n");
                set("wield_msg","$N高高舉起$n。\n");
                set("unwield_msg", "$N放下$n，有些氣喘吁吁。\n");
        }
            init_blade(20);
        setup();
}