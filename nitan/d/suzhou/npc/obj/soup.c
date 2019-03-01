// soup.c

inherit ITEM;
inherit F_LIQUID;
#include <ansi.h>
void create()
{
        set_name(HIG"荷葉冬筍湯"NOR, ({"soup"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香氣撲鼻的荷葉冬筍湯。\n");
                set("unit", "碗");
                set("value", 150);
        set("max_liquid", 4);
    }

    // because a container can contain different liquid
    // we set it to contain tea at the beginning
    set("liquid", ([
        "type": "water",
        "name": "荷葉冬筍湯",
        "remaining": 12,
        "drunk_supply": 20,
    ]));
}