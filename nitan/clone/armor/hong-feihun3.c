#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
        set_name( HIR "紅血飛魂" NOR, ({ "hongxue feihun3", "hongxue3" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("value", 2000000);
                set("armor_prop/armor", 200);
                                set("armor_prop/dex", 15);
                                set("armor_prop/damage", 300);
                                set("limit", ([ 
                                        "exp" : 30000000,
                                        "scborn" : 1,
                                ]));
                set("material", "gold");
        }
        setup();
}

int query_autoload()
{
        return 1;
}
