#include "herb.h"

void create()
{
        set_name(HIW "乳香" NOR, ({ "ru xiang", "ru", "xiang", "herb_ruxiang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "乳香是常見的中藥藥材。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 5000);
                set("base_weight", 50);
        }
        setup();
}