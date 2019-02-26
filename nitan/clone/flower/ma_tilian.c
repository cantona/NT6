// ma_tilian.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIC "馬蹄蓮" NOR, ({"mati lian", "ma"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一朵綻放着的馬蹄蓮，代表着永結同心，吉祥如意，聖潔虔誠。\n");
                set("unit", "束");
                set("base_value", 35);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower",1);
        }
        set_amount(1);
}
#include "flower.h"