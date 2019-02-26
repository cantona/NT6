// earth.c 玉髓

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "玉髓" NOR, ({ "yu sui", "earth" }) );
        set_weight(30);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", YEL "這是一塊玉髓，受中央戊己土氣所鍾而生玉魄，色黃，入手温潤。\n" NOR);
                set("value", 2000);
                set("unit", "塊");
                set("magic/element", "earth");
        }
        setup();
}
