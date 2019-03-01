// duchongfen.c
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>;
//inherit COMBINED_ITEM;
inherit ITEM;
inherit F_UNIQUE;

void create()
{
        set_name("毒蟲粉", ({ "duchong fen", "duchong", "fen" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一包以蜈蚣、蜘蛛等為原料制成的毒粉。
可以用來生成(make)火堆(huodui)。也可以倒(pour)進酒水裡，
或塗(tu)在兵器上。(塗之前必須先點燃(dian)它)\n" );
//                set("unit", "些");
                set("unit", "包");
//                set("base_value", 3000);
//                set("base_unit", "包");
//                set("base_weight", 30);
                set("drug2", __DIR__"duchongfen1");
                set("pour_type", "xx_poison");
        }
//        set_amount(1);
}
#include "poison.h";
