// caichou.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("綵綢", ({"whip"}));
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一條長長的綵綢，是用於舞蹈的道具。\n");
                set("unit", "條");
                set("value", 500);
        }
        init_whip(10);
        setup();
}
