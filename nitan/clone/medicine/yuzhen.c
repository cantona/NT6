// yuzhen.c  玉真散  by sinb

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(CYN "玉真散" NOR, ({"yuzhen san", "san"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一包玉真散，非常珍貴的療傷藥品。\n");
                set("base_unit", "包");
                set("base_value", 20000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "chuanwu"  : 1,
                                    "chaihu"  : 1,
                                    "renshen"   : 1,
                                    "chenpi"   : 1,
                                    "dangui"   : 1,
                                    "duhuo"   : 1,
                                    "moyao"    : 1,
                                    "shengdi"  : 1, ]),
                        "neili" : 70,
                        "jing"  : 25,
                        "time"  : 1,
                        "min_level" : 100,
                        "medical" : 150,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/yuzhen", me)<10 )
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

        set_temp("last_eat/yuzhen", time(), me);

        message_vision(CYN "$N" CYN "張開嘴，猛地吞下了" + name() +
                       CYN "，輕輕的哼了一聲。\n" NOR, me);

        set("eff_qi", my["max_qi"], me);
        set("qi", my["max_qi"], me);

        me->start_busy(1);

                destruct(this_object());

        return 1;
}
