#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIC"歸元丹"NOR, ({"guiyuan dan", "dan"}));
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
        int nl, mn;

        if( time()-query_temp("last_eat/dan(D, me)")<60 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        nl=query("neili", me)+500;
        mn=query("max_neili", me)*2;

        if (nl > mn)
        {
                write("你現在內力修為無需服用" + name() + "。\n");
                return 1;
        }

        set_temp("last_eat/dan(D)", time(), me);

        message_vision(HIC "$N吃下一粒歸元丹，感到內力有所補充。\n" NOR, me);
        addn("neili", 500, me);

        me->start_busy(2);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}