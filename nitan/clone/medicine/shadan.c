#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIW "田七鯊膽丸" NOR, ({"shadan wan", "wan"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "集結數中名貴藥材煉製而成的丹藥，乃是桃花島的獨門奇藥。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 5000);
                set("base_weight", 70);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "tianqi"   : 3,
                                    "shadan"   : 3,
                                    "lanhua"   : 1,
                                    "honghua"  : 1,
                                    "wulingzhi": 1,
                                    "lurong"   : 1,
                                    "zzfen"    : 1,
                                    "yjhua"    : 1,
                                    "xuejie"   : 1,
                                    "shengdi"  : 1 ]),
                        "neili" : 200,
                        "jing"  : 40,
                        "time"  : 6,
                        "min_level" : 160,
                        "taohua-yaoli" : 160,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/wuchang", me)<80 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        if( query("neili", me) >= query("max_neili", me) )
        {
                write("你現在內力飽滿，無需服用田七鯊膽丸。\n");
                return 1;
        }

        set_temp("last_eat/wuchang", time(), me);

        message_vision(HIW "$N" HIW "吞下田七鯊膽丸，長呼出一口氣，臉色變得紅潤起來。\n" NOR, me);
        tell_object(me, HIC "你只覺得真氣充沛，似乎有使不完的力氣。\n" NOR);

        my = me->query_entire_dbase();
        my["neili"] = my["max_neili"];

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
