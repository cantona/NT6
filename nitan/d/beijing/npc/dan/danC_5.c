#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIC"修羅"NOR+HIR"無常"NOR+HIY"丹"NOR, ({"xiuluo dan", "dan"}));
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

        if( time()-query_temp("last_eat/dan(C, me)")<90 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

        set_temp("last_eat/dan(C)", time(), me);

        message_vision(HIR "$N吃下一粒修羅無常丹，精力得到了完全的調整。\n" NOR, me);
        set("jingli",query("max_jingli",  me), me);

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}