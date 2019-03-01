#include "herb.h"

void create()
{
        set_name(NOR + WHT "沒藥" NOR, ({ "mo yao", "mo", "yao", "herb_moyao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "沒藥是常見的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 300);
                set("base_weight", 50);
        }
        setup();
}