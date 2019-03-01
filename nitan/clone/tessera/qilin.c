#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(YEL "麒麟﹒土" NOR, ({"qi lin", "earth"}));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", YEL "可用于鑲嵌10LV，屬性土。\n" NOR);
                set("value", 100000);
                set("unit", "塊");
                set("no_identify", 1);
        }
        setup();
}