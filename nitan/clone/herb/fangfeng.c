#include "herb.h"

void create()
{
        set_name(NOR + HIB "防風" NOR, ({ "fang feng", "fang", "feng", "herb_fangfeng" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIB "防風是常見的中藥藥材。\n" NOR);
                set("base_unit", "片");
                set("base_value", 5000);
                set("base_weight", 40);
        }
        setup();
}