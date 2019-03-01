// huojin.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(MAG "活筋舒血丸" NOR, ({"huojin wan", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", MAG "這是一粒藥丸，呈現出淡淡的粉色，療傷效果頗為不錯。\n" NOR);
                set("base_unit", "粒");
                set("base_value", 3000);
                set("base_weight", 60);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "chuanwu"  : 1,
                                    "honghua"  : 1,
                                    "dangui"   : 1,
                                    "chenpi"   : 1,
                                    "moyao"    : 1,
                                    "shengdi"  : 1,
                                    "yjhua"    : 1,
                                    "heshouwu" : 1, ]),
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
        mapping my;

        if( time()-query_temp("last_eat/huojin", me)<20 )
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

        set_temp("last_eat/huojin", time(), me);

        message_vision(MAG "$N" MAG "小心的吞下了" + name() +
                       MAG "，運了兩口氣，臉色看起來好多了。\n" NOR, me);

        me->receive_curing("qi", 350);
        me->receive_heal("qi", 350);

        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
