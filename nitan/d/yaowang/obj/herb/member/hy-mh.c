#include "herb.h"

void create()
{
        set_name(HIC "梅花還陽" NOR, ({ "hy-mh", "Rhodobryum giganteum", "herb_hy_mh" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "真酵科植物暖地大葉蘚(Rhodobryum giganteum)的全草。因其頂葉大.簇生如花苞狀，形如梅花，故得此名。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}

