#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIW"蓄精丹"NOR, ({"xujing dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "粒");
                set("base_value", 60);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/dan(A, me)")<5 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["jing"] == my["max_jing"])
        {
                write("你現在精神狀態很好，無需服用" + name() + "。\n");
                return 1;
        }

        set_temp("last_eat/dan(A)", time(), me);

        message_vision(HIW "$N吃下一粒蓄精丹，感到靈台處一片清淨。\n" NOR, me);
        me->receive_curing("jing", 100);
        me->receive_heal("jing", 100);

        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}