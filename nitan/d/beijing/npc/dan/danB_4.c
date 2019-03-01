#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(YEL"十全大還丹"NOR, ({"shiquan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "粒");
                set("base_value", 80);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/dan(B, me)")<15 )
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

        set_temp("last_eat/dan(B)", time(), me);

        message_vision(YEL "$N吃下一粒十全大還丹，感到內息得到了比較大的調整。\n" NOR, me);
        me->receive_curing("qi", 400);
        me->receive_heal("qi", 400);

        me->start_busy(2);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}