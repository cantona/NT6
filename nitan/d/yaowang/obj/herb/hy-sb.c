#include "herb.h"

void create()
{
        set_name(HIC "菱葉紅景天" NOR, ({ "hy-sb", "Rhodiola henryi", "herb_hy_sb" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "景天科植物豌豆七(又稱菱葉紅景天)(Rhodiola henryi)的帶根全草。因其有活血、止痛、消腫之功效，且藥效作用快，故名“十步還陽”和“大救駕”。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}
