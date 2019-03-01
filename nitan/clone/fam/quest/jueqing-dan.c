#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "絕情丹" NOR, ({ "jueqing dan", "jueqing", "dan" }) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這是一顆鮮紅色的丹藥，外觀甚是美麗，據說能解情花之毒。\n" NOR);
                set("value", 500000);
                set("unit", "顆");             
        }
        setup();
}

int query_autoload()
{
        return 1;
}