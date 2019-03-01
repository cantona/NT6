#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("龍涎香", ({"long xianxiang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是一塊龍涎香,用來捕蛇效果很好。\n");
                set("value", 1000);
        }
        setup();
}

int do_effect(object me)
{
        return notify_fail("想死啊？龍涎香不能吃。\n");
}
