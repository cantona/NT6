#include "herb.h"

void create()
{
        set_name(NOR + YEL "陳皮" NOR, ({ "chen pi", "chen", "pi", "herb_chenpi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "陳皮是常見的中藥藥材。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 10);
                set("base_weight", 20);
                set("no_sell", "藥王谷的丹藥非常有名，但普通草藥隨地都有啊。");
                set("yaowang", 1);
        }
        setup();
}
