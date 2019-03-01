#include "herb.h"

void create()
{
        set_name(GRN "轉筋草" NOR, ({ "zhuanjin cao", "Pachysandra terminalis", "herb_zhjcao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "黃楊科植物頂花板凳果(又稱富貴草)(Pachysandra terminalis)的帶根全草。因其有舒筋活絡功效，故得此名。\n" NOR);
                set("base_unit", "株");
                set("base_value", 60000);
                set("base_weight", 100);
        }
        setup();
}
