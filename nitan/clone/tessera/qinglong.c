#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIG "青龍·木" NOR, ({"qing long", "wood"}));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIG "可用於鑲嵌10LV，屬性木。\n" NOR);
                set("value", 100000);
                set("unit", "塊");
                set("no_identify", 1);
        }
        setup();
}
