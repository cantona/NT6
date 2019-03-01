// tongmai.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(WHT "貫氣通脈丹" NOR, ({"tongmai dan", "dan"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", WHT "這是一粒藥丸，看上去銀光閃閃，實是效果極佳療傷"
                            "聖藥。\n" NOR);
                set("base_unit", "粒");
                set("base_value", 3000);
                set("base_weight", 85);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "chuanwu"  : 1,
                                    "honghua"  : 1,
                                    "dangui"   : 1,
                                    "chenpi"   : 1,
                                    "moyao"    : 1,
                                    "shengdi"  : 1,
                                    "yjhua"    : 1,
                                    "heshouwu" : 1,
                                    "renshen"  : 1,
                                    "lurong"   : 1, ]),
                        "neili" : 150,
                        "jing"  : 40,
                        "time"  : 5,
                        "min_level" : 120,
                        "medical" : 150,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/tongmai", me)<30 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["eff_qi"] == my["max_qi"])
        {
                write("你現在並沒有受傷，不必服用" + name() + "。\n");
                return 1;
        }

        set_temp("last_eat/tongmai", time(), me);

        message_vision(WHT "$N" WHT "把" + name() +
                       WHT "咕咚一聲吞下了肚，立刻氣色看起來好多了。\n" NOR, me);

        me->receive_curing("qi", 1000);
        me->receive_heal("qi", 1000);

        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
