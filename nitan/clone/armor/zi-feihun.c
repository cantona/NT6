#include <ansi.h>
#include <armor.h>

inherit HANDS;

void create()
{
        set_name( NOR + MAG "紫雷飛魂" NOR, ({ "zilei feihun", "zilei" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("value", 2000000);
                set("armor_prop/armor", 100);
                                set("armor_prop/int", 8);
                                set("armor_prop/con", 4);
                                set("armor_prop/damage", 200);
                                set("limit", ([ 
                                        "exp" : 5000000,
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
