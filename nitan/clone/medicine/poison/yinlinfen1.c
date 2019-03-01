// yinlinfen1.c
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>;
inherit COMBINED_ITEM;

void create()
{
        set_name(WHT"點燃的銀磷粉"NOR, ({ "yinlin fen", "fen", "yinlin" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一包銀光閃閃的毒粉。已經點燃，可以塗(tu)在兵器上了。\n" );
                set("unit", "些");
                set("base_value", 5000);
                set("base_unit", "包");
                set("base_weight", 30);
                set("drug_color", ""WHT"銀光閃閃"NOR"");
                set("pour_type", "cold_poison");
        }
        set_amount(1);
}

#include "poison1.h";
