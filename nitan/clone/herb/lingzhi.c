#include "herb.h"

void create()
{
        set_name(HIG "靈芝" NOR, ({ "ling zhi", "ling", "zhi", "herb_lingzhi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "靈芝是頗為名貴的中藥藥材。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 20000);
                set("base_weight", 70);
        }
        setup();
}