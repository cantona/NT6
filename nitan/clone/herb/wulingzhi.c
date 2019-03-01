#include "herb.h"

void create()
{
        set_name(NOR + MAG "五靈脂" NOR, ({ "wu lingzhi", "wu", "lingzhi", "herb_wulingzhi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "五靈脂是常見的中藥藥材。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 5000);
                set("base_weight", 100);
        }
        setup();
}