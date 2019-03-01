// plow.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name("犁頭", ({"li tou", "plow", "li"}));
        set_weight(50000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把黑黝黝的犁頭，看上去確實只有老牛才拉得動。\n");
                set("value", 5000);
                set("material", "iron");
                set("wield_msg", "$N橫握起$n，發現實在太不適手，幹脆抱在懷裡。\n");
                set("unwield_msg", "$N放下手中的$n，累得渾身都是臭汗，就快虛脫了。\n");
        }

        init_hammer(30, TWO_HANDED);
        setup();
}
