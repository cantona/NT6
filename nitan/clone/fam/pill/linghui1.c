#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(HIY "昊天果" NOR, ({ "haotian guo", "haotian", "guo" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一枚金黃色的果實，服用後能增加人的靈慧。\n" NOR);
                set("base_unit", "枚");
                set("base_value", 6000);
                set("base_weight", 80);
                set("only_do_effect", 1);

        }
        setup();
}

int do_effect(object me)
{
        int na, un;

        na = query("name");
        un = query("base_unit");

        if( time()-query_temp("last_eat/dan(linghui, me)")<100 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }
        set_temp("last_eat/dan(linghui)", time(), me);

        message_vision(HIY "$N" HIY "一仰脖，吞下了一" + un + na +
                       HIY "。\n" NOR, me);
        addn("magic_points", 5+random(6), me);

        me->start_busy(3);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}