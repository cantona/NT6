// shitou.c

#include <weapon.h>
#include <ansi.h>
inherit HAMMER;

void create()
{
        set_name(HIW"大石頭"NOR, ({ "da shikuai", "shitou"}));
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", "這是一平平常常的大石頭。\n");
                set("value", 0);
                set("material", "stone");
                set("wield_msg", "$N搬起一塊$n準備戰鬥。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        init_hammer(1);
        setup();
}