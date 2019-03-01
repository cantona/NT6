// jiuhulu.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;
inherit F_LIQUID;

void create()
{
        set_name("酒葫蘆", ({"jiu hulu", "jiuhulu", "hulu"}));
        set_weight(350);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一個裝酒的葫蘆。\n");
                set("unit", "個");
                set("value", 30);
                set("max_liquid", 5);
                set("wield_msg", "$N抓起一個$n，握在手中當武器。\n");
                set("material", "bone");
        }

        set("liquid", ([
                "type": "water",
                "name": "米酒",
                "remaining": 5,
        ]) );
        init_hammer(5);
        setup();
}
