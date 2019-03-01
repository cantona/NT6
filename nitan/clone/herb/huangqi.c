#include "herb.h"

void create()
{
        set_name(NOR + YEL "黃□" NOR, ({ "huang qi", "huang", "qi", "herb_huangqi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "黃□是常見的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 5000);
                set("base_weight", 35);
        }
        setup();
}