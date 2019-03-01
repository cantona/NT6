inherit F_UNIQUE;
#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIW "聖火令" NOR, ({ "shenghuo ling", "ling" }) );
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else
        {
                set("unit", "把");
                set("value", 10000);
                set("material", "steel");
                set("no_sell", "他奶奶的，這種破鐵牌也值錢？");
                set("long", CYN "這是一柄兩尺來長的黑牌，非金非鐵。質"
                            "地堅硬無比，似透明，令\n中隱隱似有火燄飛"
                            "騰，實則是令質映光，顏色變幻。令上刻得有"
                            "不\n少波斯文，似乎和武學有關，內容深奧，"
                            "看來要仔細研讀一番才行。\n" NOR);
                set("wield_msg", HIR "$N" HIR "“唰”的一聲，從腰間抽"
                                 "出一片黑黝的鐵牌握在手中。\n" NOR);
                set("unwield_msg", HIR "$N" HIR "將聖火令插回腰間。\n"
                                   NOR);
                set("skill", ([
                        "name":         "shenghuo-ling",
					    "family_name" : "明教",
                        "exp_required": 1500000,
                        "jing_cost":    120,
                        "difficulty":   48,
                        "max_skill":    149,
                        "min_skill":    119,
                        "need" : ([ "sanscrit" : 150 ]),
                ]) );
        }
        init_sword(80);
        setup();
}