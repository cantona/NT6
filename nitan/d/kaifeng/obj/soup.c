inherit ITEM;
inherit F_LIQUID;

#include <ansi.h>

void create()
{
        set_name(HIY "爆姜鯽魚湯" NOR, ({"soup"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香氣撲鼻的鯽魚湯。\n");
                set("unit", "碗");
                set("value", 80);
                set("max_liquid", 4);
        }

        set("liquid", ([
                    "type": "water",
                "name": "鯽魚湯",
                "remaining": 6,
                "drunk_supply": 20,
        ]));
}
