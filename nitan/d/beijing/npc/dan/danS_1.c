#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIY"軒轅"NOR+HIW"補心"NOR+YEL"丹"NOR, ({"xuanyuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "粒");
                set("base_value", 0);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/dan(full, me)")<300 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

        set_temp("last_eat/dan(full)", time(), me);

        message_vision(HIY "$N吃下一粒軒轅補心丹，再也感覺不到任何疲憊。\n" NOR, me);
        my["jingli"] = my["max_jingli"];
        my["neili"]  = my["max_neili"];
        my["jing"]   = my["max_jing"];
        my["qi"]     = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["eff_qi"]   = my["max_qi"];

        me->start_busy(6);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}