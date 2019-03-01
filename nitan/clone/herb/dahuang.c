#include "herb.h"

void create()
{
        set_name(HIY "大黃" NOR, ({ "da huang", "da", "huang", "herb_dahuang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "大黃是頗為名貴的中藥藥材。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 7000);
                set("base_weight", 100);
        }
        setup();
}