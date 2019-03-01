#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "紫蛟皮革" NOR, ({ "dragon pige", "pige" }));
        set_weight(8000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "一張巨大蛟皮，呈紫黑色，堅硬無比。\n" NOR);
                set("unit", "張");
                set("value", 1000000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}