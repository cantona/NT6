// This program is a part of NITAN MudLIB
// tianmo.c 天魔聖血膏

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIC "天魔聖血膏" NOR, ({"tianmo shengxuegao", "tianmo", "shengxuegao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一包天魔聖血膏，天魔聖血膏是天下無雙的救傷靈藥。\n");
                set("base_unit", "包");
                set("base_value", 26000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ 
                                    "dangui"   : 1,
                                    "lurong"   : 6,
                                    "honghua"  : 3,
                                    "taoxian"  : 1,
                                    "zzfen"    : 1,
                                    "heshouwu" : 6,
                                    "renshen"  : 9,
                                    "shengdi"  : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 5,
                        "min_level" : 120,
                        "medical" : 200,
                        "liandan-shu" : 1900,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my; 

        my = me->query_entire_dbase(); 

        if( time()-query_temp("last_eat/tianmo", me) < 1800 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        set_temp("last_eat/tianmo", time(), me);

        message_vision(YEL "$N" YEL "吃下一包" + name() +
                       YEL "，內息運行一小週天，感覺身體發生了一些變化。\n", me);

        my["jing"]     = my["max_jing"];
        my["qi"]       = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["eff_qi"]   = my["max_qi"];
        my["neili"]    = my["max_neili"];
        my["jingli"]   = my["max_jingli"];
        me->start_busy(3);

        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 

        return 1;
}
