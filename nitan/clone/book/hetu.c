#include <ansi.h>
inherit BOOK;

void create()
{
        set_name(HIC "「河圖」" NOR, ({ "he tu", "he", "tu" }));
        set_weight(500);
        if (clonep())
            set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", HIY "這是一本用薄絹寫成的書。上書二字古篆「"
                            HIC "河圖" HIY "」。書皮已然\n泛黃，看來已經"
                            "保存很久了。\n" NOR);
                set("value", 1);
                set("no_sell", "嗯？你拿的這是啥破玩意？");
                set("material", "silk");
                set("skill", ([
                        "name" : "count",
                        "exp_required" : 1000000,
                        "jing_cost"  : 80,
                        "difficulty" : 80,
                        "max_skill"  : 199,
                        "min_skill"  : 100,
                        "need" : ([ "literate" : 300 ]),
                ]));
        }
}
