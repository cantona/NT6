#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIY "三黃寶臘丹" NOR, ({"baola dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "武當派的療傷聖藥，具有極佳的解毒功效。\n" NOR);
                set("base_unit", "粒");
                set("base_value", 8000);
                set("base_weight", 55);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "tenghuang" : 2,
                                    "mahuang"   : 2,
                                    "xionghuang": 2,
                                    "duhuo"     : 1,
                                    "yanwo"     : 1,
                                    "xiongdan"  : 1,
                                    "lurong"    : 1,
                                    "shancha"   : 1,
                                    "renshen"   : 1,
                                    "xuelian"   : 1,
                                    "lingzhi"   : 1, ]),
                        "neili" : 400,
                        "jing"  : 60,
                        "time"  : 8,
                        "min_level" : 150,
                        "wudang-yaoli" : 220,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat/jiedu", me)<80 )
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

        message_vision(HIY "$N" HIY "服下了一顆" + name() + HIY "，急忙"
                       "盤膝坐下，開始運功逼毒。\n" NOR, me);

        // 運功驅毒
        addn_temp("apply/dispel_poison", 350, me);
        SKILL_D("force")->exert_function(me, "dispel");
        addn_temp("apply/dispel_poison", -350, me);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
