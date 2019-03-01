#include "herb.h"

void create()
{
        set_name(HIC "太陽還陽" NOR, ({ "hy-ty", "Polygonatum hookeri", "herb_hy_ty" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "百合科植物獨花黃精(Polygonatum hookeri)的根莖。因其喜生長在向陽坡上.故得此名。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 20000);
                set("base_weight", 100);
        }
        setup();
}
