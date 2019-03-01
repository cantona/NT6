// tongren.c

#include <weapon.h>
#include <ansi.h>
inherit HAMMER;

void create()
{
        set_name(HIY"獨腳銅人"NOR, ({ "tongren" }) );
        set_weight(50000);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", "這是一隻沉重的獨腳銅人，打造的相當粗大堅實。\n");
                set("value", 3);
                set("material", "iron");
                set("wield_msg", "$N拿出一隻$n，試了試重量，然後握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        setup();
}