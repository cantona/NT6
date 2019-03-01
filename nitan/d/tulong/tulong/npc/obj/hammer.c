#include <weapon.h>
#include <ansi.h>

inherit HAMMER;

void create()
{
        set_name(HIG "碧綠" NOR+HIR "西瓜" NOR, ({ "green xigua","xigua","hammer" }) );
        set_weight(160000); // 也太重了
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "對");
                set("long", "這西瓜由精鋼鑄成，瓜上漆成綠黑間條之色，共有一對，系以鋼鏈。\n");
                set("value", 3000);
                set("material", "iron");
                set("wield_msg", "$N拿出一對$n，試了試重量，然後握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_hammer(80);
        setup();
}
