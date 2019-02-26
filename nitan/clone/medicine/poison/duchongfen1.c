// duchongfen1.c
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>;
inherit COMBINED_ITEM;

void create()
{
        set_name("點燃的毒蟲粉", ({ "duchong fen", "duchong", "fen" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一包以蜈蚣、蜘蛛等為原料製成的毒粉。已經點燃，可以塗(tu)在兵器上了。\n" );
                set("unit", "些");
                set("base_unit", "包");
                set("base_weight", 30);
                set("drug_color", ""BLU"藍光閃閃"NOR"");
                set("pour_type", "xx_poison");
        }
        set_amount(1);
}

#include "poison1.h";
