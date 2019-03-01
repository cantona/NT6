#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(MAG "紫金汲取勛章" NOR, ({ "derive emblem", "emblem" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "帶在身上可以提升汲取一倍速度的效果。\n" NOR);
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
