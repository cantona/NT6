// changqiang.c 長槍

#include <weapon.h>
inherit SPEAR;

void create()
{
        set_name("長槍", ({ "changqiang" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "桿");
                set("long", "這是一根白纓長鋼槍，長可丈二，槍頭隱隱透出寒光。\n");
                set("value", 1500);
                set("rigidity",100);
                set("material", "steel");
                set("wield_msg", "$N掣出一桿$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n反別身後。\n");
        }
          init_spear(25);
        setup();
}
