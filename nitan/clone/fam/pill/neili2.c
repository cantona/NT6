#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(HIR "火龍果" NOR, ({ "huolong guo", "huolong", "guo" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這是一枚拳頭大小的火龍果，能起到調息內力的作用。\n" NOR);
                set("base_unit", "枚");
                set("base_value", 8000);
                set("base_weight", 100);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un;

        na = query("name");
        un = query("base_unit");

        if( time()-query_temp("last_eat/dan(D, me)")<400 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        if( query("neili", me) >= query("max_neili", me)*2 )
        {
                write("你現在內力修為無需服用" + name() + "。\n");
                return 1;
        }

        set_temp("last_eat/dan(D)", time(), me);

        message_vision(HIY "$N" HIY "吞下一" + un + na + HIY "，雙目頓時精"
                       "光四射。\n" NOR, me);

        set("neili",query("max_neili",  me)*2, me);

        me->start_busy(5);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}