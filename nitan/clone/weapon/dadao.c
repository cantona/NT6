// dadao.c

#include <weapon.h>
inherit BLADE;

void create()
{
        set_name("大刀", ({ "dadao","blade" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄亮晃晃的大刀。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲從背後撥出一柄$n。\n");
                set("unwield_msg", "$N將手中的$n插回背後。\n");
        }
        init_blade(40);
        setup();
}