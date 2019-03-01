// tianxin.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIW "天心解毒丹" NOR, ({"tianxin dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一粒白色的藥丸，具有相當好的解毒效果。\n");
                set("base_unit", "粒");
                set("base_value", 5000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "yjhua"  : 1,
                                    "duhuo"  : 1,
                                    "chuanwu": 1,
                                    "chenpi" : 1,
                                    "fuzi"   : 1,
                                    "shengdi": 1,
                                    "moyao"  : 1,
                                    "xijiao" : 1,
                                    "lingzhi": 1,
                                    "gsliu"  : 1, ]),
                        "neili" : 100,
                        "jing"  : 35,
                        "time"  : 3,
                        "min_level" : 120,
                        "yaowang-miaoshu" : 120,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat/tianxin", me)<20 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        if (! me->query_skill_mapped("force"))
        {
                write("你沒有激發任何內功，怎麼發揮藥力進行驅毒？\n");
                return 1;
        }

        set_temp("last_eat/tianxin", time(), me);

        message_vision(HIY "$N" HIY "暗暗運了一口氣，服下了" + name() +
                       HIY "，盤膝坐下，開始運功逼毒。\n" NOR, me);

        // 運功驅毒
        addn_temp("apply/dispel_poison", 180, me);
        SKILL_D("force")->exert_function(me, "dispel");
        addn_temp("apply/dispel_poison", -180, me);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
