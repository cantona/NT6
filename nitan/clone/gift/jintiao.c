// jintiao.c 金條

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "金條" NOR, ({ "jin tiao", "jin", "tiao" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一根黃澄澄的金條。\n");
                set("value", 500000);
                set("unit", "根");
        }
}

int query_autoload() { return 1; }