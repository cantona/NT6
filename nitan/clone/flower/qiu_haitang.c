// qiu_haitang.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIY "秋海棠" NOR, ({"qiu haitang", "qiu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是一朵秋海棠，又名斷腸花，象征苦戀。當人們愛情遇到波折、男\n女離別時，常以秋海棠自喻。 \n");
                set("unit", "束");
                set("base_value", 35);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower",1);
        }
        set_amount(1);
}
#include "flower.h"