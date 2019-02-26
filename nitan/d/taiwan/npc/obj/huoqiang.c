// huoqiang.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>
#include <weapon.h>

inherit STAFF;

void create()
{
        set_name("荷蘭火槍", ({"helan huoqiang", "huoqiang"}));
        set_weight(5000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "一支荷蘭火槍。可惜只能放一槍。\n");
                set("value", 10000);
                set("material", "bamboo");
                set("wield_msg", "$N抽出一支烏油的木柄火槍握在手中。\n");
                set("unwield_msg", "$N把手中的火槍揹回背上。\n");
        }
        init_staff(30);
        setup();
}