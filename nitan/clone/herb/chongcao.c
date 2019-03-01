#include "herb.h"

void create()
{
        set_name(NOR + HIB "東蟲夏草" NOR, ({ "chong cao", "chong", "cao", "herb_chongcao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIB "東為蟲，夏為草。乃是極為名貴的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 10000);
                set("base_weight", 85);
        }
        setup();
}