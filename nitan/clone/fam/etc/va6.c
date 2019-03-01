#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "鑽石" NOR, ({ "zuan shi", "zuan", "shi" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "這是一顆上等鑽石，相信可以"
                            "賣個好價錢。\n");
                set("value", 200000);
                set("unit", "顆");
        }
}