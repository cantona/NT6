// qingtang.c

inherit ITEM;
inherit F_LIQUID;
#include <ansi.h>
void create()
{
        set_name(GRN"清湯"NOR, ({"qingtang"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香氣撲鼻的新鮮野菜做的湯。\n");
                set("unit", "碗");
                set("value", 80);
        set("max_liquid", 4);
    }

    // because a container can contain different liquid
    // we set it to contain tea at the beginning
    set("liquid", ([
        "type": "water",
        "name": "野菜湯",
        "remaining": 6,
        "drunk_supply": 20,
    ]));
}