#include "herb.h"

void create()
{
        set_name(NOR + MAG "靈仙" NOR, ({ "ling xian", "ling", "xian", "herb_lingxian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "靈仙是常見的中藥藥材。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 5000);
                set("base_weight", 40);
        }
        setup();
}