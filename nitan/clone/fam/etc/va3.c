#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "玉石" NOR, ({ "yu shi", "yu", "shi" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "這是一塊上等寶玉，相信可以"
                            "賣個好價錢。\n");
                set("value", 160000);
                set("unit", "塊");

        }
}