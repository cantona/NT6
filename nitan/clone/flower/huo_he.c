// huohe.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIR "火鶴" NOR, ({"huo he", "huo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是一朵嬌艷火紅的火鶴，熱情奔放，吉利，充滿喜慶、祥和、希望。\n");
                set("unit", "束");
                set("base_value", 75);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower",1);
        }
        set_amount(1);
}
#include "flower.h"