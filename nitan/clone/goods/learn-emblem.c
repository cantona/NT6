#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG "紫金學習勛章" NOR, ({ "learn emblem", "emblem" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "帶在身上可以提升學習最大次數三百次。\n" NOR);
                set("unit", "塊");
                set("can_summon", 1);
                set("value", 500000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
