#include "herb.h"

void create()
{
        set_name(HIC "巖石還陽" NOR, ({ "hy-ys", "Chlamydoboea sinensis", "herb_hy_ys" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "苦苣苔科植物寬萼苣苔(Chlamydoboea sinensis)的全草。因其多生長在巖石夯，故得此名。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

