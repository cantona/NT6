#include "herb.h"

void create()
{
        set_name(HIY "飛天蜈蚣" NOR, ({ "wugong", "Aralia chinensis", "herb_wugong" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "五加科植物□木(Aralia chinensis)的根、根皮及莖皮。因其小枝密被黃棕色針刺，猶如蜈蚣飛天，故得此名。\n" NOR);
                set("base_unit", "根");
                set("base_value", 30000);
                set("base_weight", 100);
        }
        setup();
}
