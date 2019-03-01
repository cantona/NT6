#include <ansi.h>

inherit ITEM;

void create()
{
    set_name(HIC "鮮花" NOR, ({ "flower" }) );
    set_weight(3);
    if( clonep() )
        set_default_object(__FILE__);
        else {
        set("long", "一朵鮮花。\n");
                set("unit", "朵");
                set("value", 0);
         }
    setup();
}