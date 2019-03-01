#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIR"回陽無極丹"NOR, ({"huiyang dan", "dan"}));
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

        if( time()-query_temp("last_eat/dan(B, me)")<90 )
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

        message_vision(HIR "$N吃下一粒回陽無極丹，內息得到了完全的補充。\n" NOR, me);
        set("qi",query("max_qi",  me), me);
        set("eff_qi",query("max_qi",  me), me);

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}