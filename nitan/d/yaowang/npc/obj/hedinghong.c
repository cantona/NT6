#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR"鶴頂紅"NOR, ({"he dinghong"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "滴");
                set("long", "這是一滴鶴頂紅，奇毒無比。\n");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}
