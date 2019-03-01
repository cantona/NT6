#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "瑪瑙" NOR, ({ "ma nao", "ma", "nao" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "這是一塊上等瑪瑙，相信可以"
                            "賣個好價錢。\n");
                set("value", 120000);
                set("unit", "塊");

        }
}