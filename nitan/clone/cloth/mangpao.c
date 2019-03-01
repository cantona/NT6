// mangpao.c 
// Last Modified by winder on May. 25 2001

#include <armor.h>
inherit CLOTH;

void create()
{
        set_name("大紅蟒袍", ({"dahong mangpao", "pao", "cloth"}));
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一件大紅色的長袍，上繡一條青龍，還有日月山河的圖形。\n");
                set("material", "cloth");
                set("unit", "件");
                set("value", 7000);
                set("armor_prop/armor", 15);

        }
        setup();
}
