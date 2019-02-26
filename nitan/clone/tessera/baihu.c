#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIY "白虎·金" NOR, ({"bai hu", "metal"}));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIY "可用於鑲嵌10LV，屬性金。\n" NOR);
                set("value", 100000);
                set("unit", "塊");
                set("no_identify", 1);
        }
        setup();
}
