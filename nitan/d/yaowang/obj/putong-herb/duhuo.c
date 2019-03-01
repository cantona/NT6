#include "herb.h"

void create()
{
        set_name(NOR + HIB "獨活" NOR, ({ "du huo", "du", "huo", "herb_duhuo" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + HIB "獨活是常見的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 4000);
                set("base_weight", 50);
                set("no_sell", "藥王谷的丹藥非常有名，但普通草藥隨地都有啊。"); 
                set("yaowang", 1); 
        }
        setup();
}
