#include "herb.h"

void create()
{
        set_name(NOR + CYN "柴胡" NOR, ({ "chai hu", "chai", "hu", "herb_chaihu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + CYN "柴胡是常見的中藥藥材。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 4000);
                set("base_weight", 60);
                set("no_sell", "藥王谷的丹藥非常有名，但普通草藥隨地都有啊。");
                set("yaowang", 1);
        }
        setup();
}
