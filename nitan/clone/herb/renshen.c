#include "herb.h"

void create()
{
        set_name(HIW "人參" NOR, ({ "ren shen", "ren", "shen", "herb_renshen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "人參是頗為名貴的中藥藥材。\n" NOR);
                set("base_unit", "根");
                set("base_value", 10000);
                set("base_weight", 90);
                set("cure_s",100);
                set("cure_d",0);
                set("cure_n",0);
        }
        setup();
}