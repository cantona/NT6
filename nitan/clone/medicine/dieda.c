// dieda.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(CYN "跌打傷癒膏" NOR, ({"dieda gao", "gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN "這是一塊膠狀的東西，療傷效果比金創藥要好一些。\n" NOR);
                set("base_unit", "包");
                set("base_value", 1500);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "chuanwu"  : 1,
                                    "honghua"  : 1,
                                    "dangui"   : 1,
                                    "chenpi"   : 1,
                                    "moyao"    : 1,
                                    "shengdi"  : 1, ]),
                        "neili" : 70,
                        "jing"  : 25,
                        "time"  : 1,
                        "min_level" : 50,
                        "medical" : 80,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/dieda", me)<10 )
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

        set_temp("last_eat/dieda", time(), me);

        message_vision(CYN "$N" CYN "張開嘴，猛地吞下了" + name() +
                       CYN "，輕輕的哼了一聲。\n" NOR, me);

        me->receive_curing("qi", 100);
        me->receive_heal("qi", 100);

        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}