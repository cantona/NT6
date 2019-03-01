#include "herb.h"

void create()
{
        set_name(NOR + WHT "蘇木" NOR, ({ "su mu", "su", "mu", "herb_sumu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "蘇木是常見的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 5000);
                set("base_weight", 60);
        }
        setup();
}