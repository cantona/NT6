#include "herb.h"

void create()
{
        set_name(HIW "太白人蔘" NOR, ({ "taibai renshen", "Pedicularis decora", "herb_tbrenshen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "玄蔘科植物美觀馬先蒿(Pedicularis decora)的根莖。因其根形略似人蔘，且有類似人蔘的功效，太白山有產，故得此名。\n" NOR);
                set("base_unit", "株");
                set("base_value", 60000);
                set("base_weight", 100);
        }
        setup();
}
