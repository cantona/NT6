#include "herb.h"

void create()
{
        set_name(NOR + HIB "鯊膽" NOR, ({ "sha dan", "sha", "dan", "herb_shadan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIB "海中鯊魚的膽臟，是非常名貴的中藥藥材。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 10000);
                set("base_weight", 35);
        }
        setup();
}