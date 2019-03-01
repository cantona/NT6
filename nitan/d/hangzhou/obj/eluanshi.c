// eluanshi.c

#include <weapon.h>
#include <ansi.h>
inherit THROWING;

void create()
{
        set_name(HIC"鵝卵石"NOR, ({ "eluan shi", "shi"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "些");
                set("long", "這是一粒平平常常的鵝卵石。\n");
                set("base_unit", "粒");
                set("base_weight", 300);
                set("value", 0);
                set("material", "stone");
                set("wield_msg", "$N掏出一粒$n準備戰鬥。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        set_amount(10);
        init_throwing(1);
        setup();
}