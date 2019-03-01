// diaogan.c

#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("釣桿", ({ "diao gan" }));
        set_weight(5000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根細長的鐵桿，猛然一看不過是根普通釣魚用的吊桿。\n");
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N抽出一根$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        setup();
}