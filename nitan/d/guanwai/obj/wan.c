inherit ITEM;
inherit F_LIQUID;
#include <ansi.h>
void create()
{
        set_name(GRN"粗瓷碗"NOR, ({"wan"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗熱氣騰騰的粥。\n");
                set("unit", "碗");
                set("value", 20);
                set("max_liquid", 20);
    }

    set("liquid", ([
        "type": "water",
        "name": "熱粥",
        "remaining": 20,
        "drunk_supply": 40,
    ]));
}
