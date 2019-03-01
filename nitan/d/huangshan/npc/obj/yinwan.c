// yinwan.c

#include <weapon.h>
inherit THROWING;
void create()
{
        set_name("銀丸", ({ "ball", "silver ball" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一粒拇指大小的銀丸。\n");
                set("unit", "堆");
                set("base_unit", "粒");
                set("base_weight", 1);
                set("base_value", 1);
        }
        set_amount(50);
        init_throwing(1);
        setup();
}