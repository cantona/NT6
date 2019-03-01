// dart.c

#include <weapon.h>
inherit THROWING;

void create()
{
        set_name("七寸長的短劍", ({ "short sword", "sword" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "精光四射的短劍，劍長七寸，劍柄兩寸。\n");
                set("unit", "把");
                set("base_unit", "把");
                set("base_weight", 40);
                set("value", 5);
        }
        set_amount(1);
        init_throwing(20);
        setup();
}