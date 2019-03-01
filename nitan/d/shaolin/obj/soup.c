inherit ITEM;
inherit F_LIQUID;

#include <ansi.h>

void create()
{
        set_name(GRN "酸菜粉絲湯" NOR, ({"soup"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一碗香氣撲鼻的酸菜粉絲湯。\n");
                set("unit", "碗");
                set("value", 160);
                set("max_liquid", 8);
        }

        set("liquid", ([
                "type": "water",
                "name": "酸菜粉絲湯",
                "remaining": 12,
                "drunk_supply": 40,
        ]));
}