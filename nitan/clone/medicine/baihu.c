#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIW "白虎奪命丹" NOR, ({"duoming dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "武當派的療傷聖藥，可治療各種內傷，效果顯著。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 8000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "tianqi"   : 1,
                                    "juhua"    : 1,
                                    "zihua"    : 1,
                                    "lanhua"   : 1,
                                    "niuxi"   : 1,
                                    "xiefen"   : 1,
                                    "moyao"    : 1,
                                    "shengdi"  : 1,
                                    "yjhua"    : 1,
                                    "renshen"  : 1,
                                    "guiwei"   : 1,
                                    "chenpi"   : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 7,
                        "min_level" : 140,
                        "wudang-yaoli" : 180,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/duoming", me)<120 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        set_temp("last_eat/duoming", time(), me);

        message_vision(HIW "$N" HIW "服下一顆" + name() + HIW "，雙目微閉，將丹藥效力全數吸收。\n" NOR, me);
        tell_object(me, HIW "突然間你覺得血脈暢通，精神飽滿之極。\n" NOR);

        log_file("static/using", sprintf("%s(%s) eat 白虎奪命丹 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        my = me->query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];

        me->start_busy(2);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
