#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(CYN"鎖泉丹"NOR, ({"suoquan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "粒");
                set("base_value", 70);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;
        int jl, mj;

        if( time()-query_temp("last_eat/dan(C, me)")<60 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        jl=query("jingli", me)+220;
        mj=query("max_jingli", me)*2;

        if (jl > mj)
        {
                write("你現在精力修為無需服用" + name() + "。\n");
                return 1;
        }

        set_temp("last_eat/dan(C)", time(), me);

        message_vision(CYN "$N吃下一粒鎖泉丹，精神隨之一震，精力有所提高。\n" NOR, me);
        addn("jingli", 220, me);

        me->start_busy(2);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}