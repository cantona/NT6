// red3.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIR "百園紅霞" NOR, ({"baiyuan hongxia", "mudan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR"這是一朵雍容華貴的紅色牡丹花，花朵婀娜多姿，委實令人心醉神迷。\n"NOR);
                set("unit", "束");
                set("base_value", 100);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower",1);
        }
        set_amount(1);
}
#include "/clone/flower/flower.h"