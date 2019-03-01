#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(HIR "朱果" NOR, ({ "zhu guo", "zhu", "guo", "zhuguo" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這是一枚火紅色的朱果，能起到調息內力的作用。\n" NOR);
                set("base_unit", "枚");
                set("base_value", 3000);
                set("base_weight", 80);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un;
        mapping my;

        na = query("name");
        un = query("base_unit");

        if( time()-query_temp("last_eat/dan(D, me)")<240 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        if( query("neili", me) >= query("max_neili", me) )
        {
                write("你現在內力修為無需服用" + name() + "。\n");
                return 1;
        }

        my = me->query_entire_dbase();

        set_temp("last_eat/dan(D)", time(), me);

        message_vision(HIY "$N" HIY "吞下一" + un + na + HIY "，內息得到了"
                       "完全的補充。\n" NOR, me);

        my["neili"] = my["max_neili"];

        me->start_busy(3);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
