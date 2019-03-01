#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(YEL"小還丹"NOR, ({"xiaohuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "粒");
                set("base_value", 50);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/dan(B, me)")<10 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["qi"] == my["max_qi"])
        {
                write("你現在體力充沛，無需服用" + name() + "。\n");
                return 1;
        }

//        me->set_temp("last_eat/dan(B)", time());

        message_vision(YEL "$N吃下一粒小還丹，感到內息得到了調整。\n" NOR, me);
        me->receive_curing("qi", 100);
        me->receive_heal("qi", 100);

        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}