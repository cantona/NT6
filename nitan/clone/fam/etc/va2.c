#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIC "翡翠" NOR, ({ "fei cui", "fei", "cui" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "這是一塊上等翡翠，相信可以"
                            "賣個好價錢。\n");
                set("value", 180000);
                set("unit", "塊");
        }
}