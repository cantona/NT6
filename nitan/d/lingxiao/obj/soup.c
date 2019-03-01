inherit ITEM;
inherit F_LIQUID;

#include <ansi.h>

void create()
{
        set_name(HIC "雪鶴湯" NOR, ({"soup"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香氣撲鼻的雪鶴湯。\n");
                set("unit", "碗");
                set("value", 80);
                set("max_liquid", 4);
        }

        set("liquid", ([
                    "type": "water",
                "name": "雪鶴湯",
                "remaining": 6,
                "drunk_supply": 20,
        ]));
}
