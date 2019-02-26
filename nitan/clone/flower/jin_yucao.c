// jin_yucao.c
// Last Modified by winder on Aug. 18 2002

#include <ansi.h>
inherit COMBINED_ITEM;
int value() { return query_amount() * (int)query("base_value"); }

void create()
{
        set_name(HIY "金魚草" NOR, ({"jinyu cao", "jin"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是一朵花型別致，似咧嘴微笑的金魚草，象徵有金有餘，鴻運當頭。\n");
                set("unit", "束");
                set("base_value", 25);
                set("base_unit", "朵");
                set("base_weight", 100);
                set("flower",1);
        }
        set_amount(1);
}
#include "flower.h"