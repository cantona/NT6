#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(HIW "昊天丹" NOR, ({ "haotian dan", "haotian", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "這是一顆精煉而成的昊天丹，服用後能增加靈慧。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 10000);
                set("base_weight", 50);
                set("only_do_effect", 1);

        }
        setup();
}

int do_effect(object me)
{
        int na, un;

        na = query("name");
        un = query("base_unit");

        if( time()-query_temp("last_eat/dan(linghui, me)")<200 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }
        set_temp("last_eat/dan(linghui)", time(), me);

        message_vision(HIY "$N" HIY "一仰脖，吞下了一" + un + na +
                       HIY "。\n" NOR, me);
        addn("magic_points", 12+random(14), me);

        me->start_busy(3);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}