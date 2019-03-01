#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(GRN "竹簡" NOR, ({ "zhu jian", "zhu", "jian" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "卷");
                set("long", GRN "一卷非常陳舊的竹簡，但保存得尚算完好，竹簡上密"
                            "密麻麻寫\n滿了小字，也不知是什麼內容。\n" NOR);
                set("value", 1);
                set("no_sell", "快拿走，什麼破玩意？");
                set("material", "bamboo");
                set("skill", ([
                        "name" : "leiting-fu",
                        "exp_required" : 1000000,
                        "jing_cost"  : 100,
                        "difficulty" : 100,
                        "max_skill"  : 299,
                        "min_skill"  : 0,
                        "need" : ([ "muslim" : 200 ]),
                ]));
        }
}