#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(YEL "竹簡" NOR, ({ "zhu jian", "zhu", "jian" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "卷");
                set("long", YEL "一卷非常陳舊的竹簡，系在上面的皮革都已斷裂，竹"
                            "簡上密密\n麻麻寫滿了小字，也不知是什麼內容。\n" NOR);
                set("value", 1);
                set("no_sell", "快拿走，什麼破玩意？");
                set("material", "bamboo");
                set("skill", ([
                        "name" : "zhuangzi-wu",
                        "exp_required" : 1500000,
                        "jing_cost"  : 120,
                        "difficulty" : 120,
                        "max_skill"  : 179,
                        "min_skill"  : 0,
                        "need" : ([ "muslim" : 250,
                                    "literate" : 250 ]),
                ]));
        }
}