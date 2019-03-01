#include "herb.h"

void create()
{
        set_name(NOR + WHT "犀角" NOR, ({ "xi jiao", "xi", "jiao", "herb_xijiao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "犀牛的角，藥性強烈，是名貴的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 10000);
                set("base_weight", 35);
        }
        setup();
}