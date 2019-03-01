// sea-wood.c
#include <weapon.h>

inherit SWORD;

void create()
{
        set_name("南海神木", ({ "sea wood", "wood", "sword" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一根遍體發出青光的劍形木棍。\n");
                set("value", 2000);
                set("material", "wood");
                set("wield_msg", "$N從背後將南海神木拔出來，拿在手中。\n");
                set("unwield_msg", "$N將手中的$n重新插回背後。\n");
                set("stable", 90);
        }
        init_sword(55);
        setup();
}
