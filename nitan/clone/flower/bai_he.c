// bai_he.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIC "百合" NOR, ({"bai he", "bai"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是一朵典雅孤傲的百合花，花的鱗莖乳白似玉，瓣瓣緊抱，\n由二、三十瓣重疊累生在一起，好象百片合成，隱含著“百\n年好合，百事合心”之意。\n");
                set("unit", "束");
                set("base_value", 45);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower", 1);
        }
        set_amount(1);
}
#include "flower.h"