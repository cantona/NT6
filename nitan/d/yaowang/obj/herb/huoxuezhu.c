#include "herb.h"

void create()
{
        set_name(HIB "活血珠" NOR, ({ "huoxuezhu", "Pleione bulbocodioides", "herb_hxzhu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "蘭科植物獨蒜蘭(Pleione bulbocodioides)的假鱗莖。因其假鱗莖底部圓形似珠，具舒筋活血功效，故得此名。\n" NOR);
                set("base_unit", "根");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}
