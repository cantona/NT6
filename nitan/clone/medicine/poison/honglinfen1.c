// honglinfen1.c
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>;
inherit COMBINED_ITEM;

void create()
{
        set_name(HIR"點燃的紅磷粉"NOR, ({ "honglin fen", "fen", "honglin" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一包腥紅色的毒粉。已經點燃，可以塗(tu)在兵器上了。\n" );
                set("unit", "些");
                set("base_value", 5000);
                set("base_unit", "包");
                set("base_weight", 30);
                set("drug_color", ""HIR"紅光閃閃"NOR"");
                set("pour_type", "hot_poison");
        }
        set_amount(1);
}

#include "poison1.h";