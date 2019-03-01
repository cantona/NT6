#include <ansi.h>
inherit ITEM;

inherit F_LIQUID;

void create()
{
        set_name(HIW "□杯" NOR, ({ "god cup", "god", "cup" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "□□所制的□杯，似乎可以□□好□□。\n" NOR);
                set("unit", "□");
                set("value", 500000);
                set("max_liquid", 100);
        }
        set("liquid", ([
                "type"        : "water",
                "name"        : HIW "□水" NOR,
                "remaining"   : 100,
                "drunk_supply": 100,
        ]));
}

int query_autoload()
{
        return 1;
}