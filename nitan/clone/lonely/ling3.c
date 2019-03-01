#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(NOR + YEL "聖火令" NOR, ({ "shenghuo ling", "shenghuo", "ling" }));
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "柄");
                set("value", 10000);
                set("material", "steel");
                set("no_sell", "他奶奶的，這種破鐵牌也值錢？");
                set("long", NOR + YEL "
這是一柄兩尺來長的黑牌，看上去非金非鐵，但質地卻是堅硬
無比。整個令牌竟有若透明，令中隱隱似有火燄飛騰，實則是
令質映光，顏色變幻。令上刻得有不少波斯文，所記似乎和武
學有關，內容深奧，看來需要仔細研讀一番才能夠領悟。\n" NOR);
                set("wield_msg", HIR "$N" HIR "從腰間抽出一片黑黝的"
                                 "鐵牌握在手中。\n" NOR);
                set("unwield_msg", HIR "$N" HIR "單手一抖，已將聖火"
                                 "令插回了腰間。\n" NOR);
                set("skill", ([
                        "name"         : "shenghuo-ling",
                        "exp_required" : 1500000,
                        "jing_cost"    : 120,
                        "difficulty"   : 80,
                        "max_skill"    : 149,
                        "min_skill"    : 120,
                        "need"         : ([ "sanscrit" : 200 ]),
                ]));
        }
        init_sword(80);
        setup();
}