#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIM"龍涎丹"NOR, ({"longxian dan", "dan"}));
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

        if( time()-query_temp("last_eat/dan(M, me)")<400 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

//        me->set_temp("last_eat/dan(M)", time());

        if (me->improve_neili(1))
        {
                message_vision(HIM "$N" HIM "吃下一粒龍涎丹，臉上閃過一道紫氣。\n" NOR, me);
                tell_object(me, "你感到內力又雄厚了一些。\n");
        } else
        {
                message_vision(HIC "$N" HIC "吃下一粒龍涎丹，臉色變了變，閃過一絲青氣。\n" NOR, me);
                tell_object(me, "你感到內息澎湃，難以吸收丹藥的效力。\n");
        }

//        me->start_busy(6);
        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}