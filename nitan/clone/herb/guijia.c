#include "herb.h"

void create()
{
        set_name(HIB "龜甲" NOR, ({ "gui jia", "gui", "jia", "herb_guijia" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "烏龜的殼，上面有各種花紋，可以入藥。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 5000);
                set("base_weight", 80);
        }
        setup();
}