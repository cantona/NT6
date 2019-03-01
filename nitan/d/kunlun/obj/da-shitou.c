// da-shitou.c

#include <weapon.h>;
#include <ansi.h>;
inherit HAMMER;

void create()
{
        set_name(HIY"大石頭"NOR,({ "da shitou", "shitou" }) );
        set_weight(2000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("value", 0);
                set("material", "bamboo");
                set("long", "這是一個大石頭。\n");
                set("wield_msg", "$N拿出一個$n，試了試重量後握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        init_hammer(8);
        setup();
}