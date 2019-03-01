// hu_dielan.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIM "蝴蝶蘭" NOR, ({"hudie lan", "hu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是一朵燦爛的蝴蝶蘭，花形似彩蝶，花姿優美動人，隱喻著“我愛你”之意。\n");
                set("unit", "束");
                set("base_value", 100);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower",1);
        }
        set_amount(1);
}
#include "flower.h"