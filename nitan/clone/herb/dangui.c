#include "herb.h"

void create()
{
        set_name(HIG "當歸" NOR, ({ "dang gui", "dang", "gui", "herb_dangui" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "當歸是常見的中藥藥材。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 1000);
                set("base_weight", 70);
        }
        setup();
}