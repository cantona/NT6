#include "herb.h"

void create()
{
        set_name(NOR + WHT "川烏" NOR, ({ "chuan wu", "chuan", "wu", "herb_chuanwu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "川烏是常見的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 200);
                set("base_weight", 50);
                set("no_sell", "藥王谷的丹藥非常有名，但普通草藥隨地都有啊。");
                set("yaowang", 1);
        }
        setup();
}
