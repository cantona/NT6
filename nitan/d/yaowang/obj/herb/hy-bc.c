#include "herb.h"

void create()
{
        set_name(HIC "八寶" NOR, ({ "hy-bc", "Sedum erythrostictum", "herb_hy_bc" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "景天科植物八寶(又稱景天)(Sedum erythrostictum)的全草。因其葉形如包菜葉，又稱包菜還陽。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}
