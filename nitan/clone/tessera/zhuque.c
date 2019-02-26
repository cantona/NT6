#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIR "朱雀·火" NOR, ({"zhu que", "fire"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIR "可用於鑲嵌10LV，屬性火。\n" NOR);
                set("value", 100000);
                set("unit", "塊");
                set("no_identify", 1); 
        }
        setup();
}
