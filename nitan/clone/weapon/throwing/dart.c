// dart.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit THROWING;

void create()
{
        set_name("毒鏢", ({ "biao" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",
"飛鏢是一種十分常見的暗器，而毒鏢卻只有一個人有．\n");
                set("unit", "些");
                set("base_unit", "枝");
                set("base_weight", 40);
                set("base_value", 0);
        }
        set("value", 0);
        set_amount(30);
        init_throwing(20);
        setup();
}
