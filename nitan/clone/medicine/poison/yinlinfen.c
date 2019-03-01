// yinlinfen.c
// Last Modified by winder on Feb. 28 2001
// Last Modified by qingyun 04.9.27

#include <ansi.h>;
//inherit COMBINED_ITEM;
inherit ITEM;
inherit F_UNIQUE;

void create()
{
        set_name(WHT"銀磷粉"NOR, ({ "yinlin fen", "fen", "yinlin" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","一包以骨灰、蛇膽等為原料制成的銀光閃閃的毒粉。
可以用來生成(make)火堆(huodui)。也可以倒(pour)進酒水裡，
或塗(tu)在兵器上。(塗之前必須先點燃(dian)它)\n" );
                set("unit", "包");
//                set("unit", "些");
//                set("base_value", 5000);
//                set("base_unit", "包");
//                set("base_weight", 30);
                set("drug2", __DIR__"yinlinfen1");
                set("pour_type", "cold_poison");
        }
//        set_amount(1);
}

#include "poison.h";
