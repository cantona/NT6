// shi_hulan.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIC "石斛蘭" NOR, ({"shihu lan", "shi"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是一朵花繁似錦，美豔絕倫的石斛蘭，花瓣外觀雅緻絢麗，\n花朵中央有紫墨色的花暈，代表着“愛你永不變”。\n");
                set("unit", "束");
                set("base_value", 45);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower",1);
        }
        set_amount(1);
}
#include "flower.h"