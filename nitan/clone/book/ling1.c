#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(CYN "聖火令" NOR, ({ "shenghuo ling", "shenghuo", "ling" }) );
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "柄");
                set("value", 10000);
                set("material", "steel");
                set("no_sell", "他奶奶的，這種破鐵牌也值錢？");
                set("long", NOR + CYN "
這是一柄兩尺來長的黑牌，非金非鐵。質地堅硬無比，似透明
令中隱隱似有火焰飛騰，實則是令質映光，顏色變幻。令上刻
得有不少波斯文，似乎和武學有關，內容深奧，看來要仔細研
讀一番才行。\n" NOR);
                set("wield_msg", HIR "$N" HIR "“唰”的一聲，從腰間抽出一片黑黝的鐵牌握在手中。\n" NOR);
                set("unwield_msg", HIR "$N" HIR "將聖火令插回腰間。\n" NOR);
                set("skill", ([
                        "name":         "shenghuo-ling",
		                "family_name" : "明教",
                        "exp_required": 1000000,
                        "jing_cost":    80,
                        "difficulty":   46,
                        "max_skill":    49,
                        "min_skill":    0,
                        "need" : ([ "sanscrit" : 150 ]),
                ]) );
        }
        init_sword(80);
        setup();
}