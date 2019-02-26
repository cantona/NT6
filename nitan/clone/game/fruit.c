#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;

void create()
{
        set_name(HIY "果汁冰" NOR, ({"fruit water","fruit"}));
        set_weight(700);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long",HIG "這是一杯由新鮮橘汁製成的果汁冰，冰得剛好，看起來誘人極了。\n" NOR);
                set("unit", "杯");
                set("value", 100);
                set("max_liquid", 5);
        }

        set("liquid", ([
                "type": "water",
                 "name":HIY "果汁冰" NOR,
                "remaining": 5,
                "supply": 10,
                "drunk_apply": 3,
        ]));
}
