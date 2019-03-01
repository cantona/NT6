// shengsheng.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIR "生生造化丹" NOR, ({"shengsheng dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一顆紅色的藥丸，具有神奇的療效。\n");
                set("base_unit", "顆");
                set("base_value", 8000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "tianqi"   : 1,
                                    "gsliu"    : 1,
                                    "duhuo"    : 1,
                                    "lurong"   : 1,
                                    "juhua"    : 1,
                                    "honghua"  : 1,
                                    "hafen"    : 1,
                                    "xiongdan" : 1,
                                    "heshouwu" : 1,
                                    "renshen"  : 1,
                                    "xuelian"  : 1,
                                    "dangui"   : 1,
                                    "chenpi"   : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 7,
                        "min_level" : 140,
                        "yaowang-miaoshu" : 220,
                        "liandan-shu" : 1900,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/jiuhua", me)<120 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        set_temp("last_eat/shengsheng", time(), me);

        message_vision(HIG "$N" HIG "慢慢服下一顆" + name() +
                       HIG "，呼吸吐納，將丹藥效力全數吸收。\n" NOR, me);
        tell_object(me, HIG "不一會兒你只覺得精神飽滿，神氣完足，內力充沛之極。\n" NOR);

        log_file("static/using", sprintf("%s(%s) eat 生生造化丹 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        my = me->query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        if (my["jingli"] < my["max_jingli"])
                my["jingli"] = my["max_jingli"];
        if (my["neili"] < my["max_neili"])
                my["neili"] = my["max_neili"];

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
