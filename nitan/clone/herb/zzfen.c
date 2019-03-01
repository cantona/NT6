#include "herb.h"

void create()
{
        set_name(HIW "珍珠粉" NOR, ({ "zhenzhu fen", "zhenzhu", "fen", "herb_zzfen" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "珍珠磨成的粉末，藥性溫和，亦有養顏之功。\n" NOR);
                set("base_unit", "包");
                set("base_value", 10000);
                set("base_weight", 30);
        }
        setup();
}