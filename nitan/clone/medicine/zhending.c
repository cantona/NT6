#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(YEL "固元鎮定散" NOR, ({"zhending san", "san"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "這是一包淡黃色的粉末，具有神奇的鎮定效果。\n" NOR);
                set("base_unit", "包");
                set("base_value", 5000);
                set("base_weight", 60);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "chuanwu"  : 1,
                                    "xuejie"   : 1,
                                    "yjhua"    : 1,
                                    "xiongdan" : 1,
                                    "shancha"  : 1,
                                    "gsliu"    : 1,
                                    "zzfen"    : 1,
                                    "xuelian"  : 1,
                                    "lurong"   : 1, ]),
                        "neili" : 150,
                        "jing"  : 60,
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

        if( time()-query_temp("last_eat/zhending", me)<10 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["eff_jing"] == my["max_jing"])
        {
                write("你現在精神狀態很好，無需服用" + name() + "。\n");
                return 1;
        }

        set_temp("last_eat/zhending", time(), me);

        message_vision(YEL "$N" YEL "一張嘴，吞下了" + name() +
                       YEL "，看上去精神好多了。\n" NOR, me);

        me->receive_curing("jing", 300);
        me->receive_heal("jing", 300);

        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
