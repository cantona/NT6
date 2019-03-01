#include "herb.h"

void create()
{
        set_name(HIW "雪蓮" NOR, ({ "xue lian", "xue", "lian", "herb_xuelian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "雪蓮是頗為名貴的中藥藥材。\n" NOR);
                set("base_unit", "朵");
                set("base_value", 30000);
                set("base_weight", 40);
        }
        setup();
}