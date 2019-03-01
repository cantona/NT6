#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "紫蛟皮" NOR, ({ "dragon skin", "skin" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + MAG "一塊蛟皮，呈紫黑色，堅硬無比，乃上等皮革原料。\n" NOR);
                set("unit", "塊");
                set("value", 100000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}