#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIW"羅剎"NOR+HIR"無常"NOR+HIY"丹"NOR, ({"luosha dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "粒");
                set("base_value", 150);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/dan(D, me)")<300 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

        set_temp("last_eat/dan(D)", time(), me);

        message_vision(HIR "$N吃下一粒羅剎無常丹，內力得到了完全的補充。\n" NOR, me);
        set("neili",query("max_neili",  me), me);

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}