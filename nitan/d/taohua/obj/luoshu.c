#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIC "「洛書」" NOR, ({ "luo shu", "luo", "shu" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", HIY "這是一本用薄絹寫成的書。上書二字古篆「"
                            HIC "洛書" HIY "」。書皮已然\n泛黃，看來已經"
                            "保存很久了。\n" NOR);
                set("value", 1);
                set("no_sell", "嗯？你拿的這是啥破玩意？");
                set("material", "silk");
                set("skill", ([
                        "name" : "count",
                        "exp_required" : 1000000,
                        "jing_cost"  : 120,
                        "difficulty" : 120,
                        "max_skill"  : 299,
                        "min_skill"  : 200,
                        "need" : ([ "literate" : 300 ]),
                ]));
        }
}