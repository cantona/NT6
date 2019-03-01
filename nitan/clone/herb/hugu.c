#include "herb.h"

void create()
{
        set_name(HIW "虎骨" NOR, ({ "hu gu", "hu", "gu", "herb_hugu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "成年虎的骨頭，藥性強烈，是非常名貴的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 12000);
                set("base_weight", 100);
        }
        setup();
}