// sanhuang.c  三黃寶臘丹   by sinb

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIY "三黃" HIR"寶臘丹" NOR, ({"baola dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一顆黃黃的藥丸，是武當派的療傷聖藥，珍貴無比。\n");
                set("base_unit", "顆");
                set("base_value", 50000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "niuhuang"   : 1,
                                    "dahuang"   : 1,
                                    "shengdi"  : 1,
                                    "lurong"   : 1,
                                    "xiefen"   : 1,
                                    "honghua"  : 1,
                                    "moyao"    : 1,
                                    "zzfen"    : 1,
                                    "heshouwu" : 1,
                                    "renshen"  : 1,
                                    "dangui"   : 1,
                                    "chenpi"   : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 5,
                        "min_level" : 150,
                        "medical" : 250,
                        "liandan-shu" : 1900,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/sanhuang", me)<120 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        set_temp("last_eat/sanhuang", time(), me);

        message_vision(YEL "$N" YEL "吃下一粒" + name() +
                       YEL "，頭上"MAG"紫氣"YEL"氤氲升起。\n", me);
        tell_object(me, YEL "不一會兒你只覺得精神飽滿，神氣完足，內力充沛之極。\n" NOR);

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
