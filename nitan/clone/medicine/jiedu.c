// jiedu.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIY "牛黃解毒丸" NOR, ({"jiedu wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一粒黃色的藥丸，用牛黃輔以原料制成，具有不"
                            "錯的解毒效果。\n" NOR);
                set("base_unit", "粒");
                set("base_value", 3000);
                set("base_weight", 55);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "yjhua"  : 1,
                                    "juhua"  : 1,
                                    "xuejie" : 1,
                                    "chenpi" : 1,
                                    "xiefen" : 1,
                                    "shengdi": 1,
                                    "lanhua" : 1,
                                    "gsliu"  : 1, ]),
                        "neili" : 80,
                        "jing"  : 30,
                        "time"  : 3,
                        "min_level" : 80,
                        "medical" : 100,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat/jiedu", me)<20 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        if (! me->query_skill_mapped("force"))
        {
                write("你沒有激發任何內功，怎麼發揮藥力進行驅毒？\n");
                return 1;
        }

        set_temp("last_eat/jiedu", time(), me);

        message_vision(HIY "$N" HIY "暗暗運了一口氣，服下了" + name() +
                       HIY "，盤膝坐下，開始運功逼毒。\n" NOR, me);

        // 運功驅毒
        addn_temp("apply/dispel_poison", 100, me);
        SKILL_D("force")->exert_function(me, "dispel");
        addn_temp("apply/dispel_poison", -100, me);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
