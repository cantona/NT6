#include "herb.h"

void create()
{
        set_name(HIY "麻黃" NOR, ({ "ma huang", "ma", "huang", "herb_mahuang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "麻黃是常見的中藥藥材。\n" NOR);
                set("base_unit", "包");
                set("base_value", 1000);
                set("base_weight", 50);
        }
        setup();
}