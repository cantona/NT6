#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIW "萬壽丹" NOR, ({"wanshou dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "粒");
                set("no_drop", "這樣東西不能離開你。\n");
                set("no_sell", "這樣東西不能離開你。\n");
                set("no_put", "這樣東西不能放在那兒。\n");
                set("no_get", "這樣東西不能離開那兒。\n");
                set("no_steal", "這樣東西不能離開那兒。\n");
                set("no_beg", "這樣東西不能離開那兒。\n");
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

        if(me->improve_neili(5))
                message_vision(HIW "$N" HIW "吃下一粒萬壽丹，感到內力又雄厚了一些。\n" NOR, me); 
        else
                message_vision(HIW "$N" HIW "吃下一粒萬壽丹，感覺好像沒什麼效果。\n" NOR, me); 

        me->start_busy(1);  

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}

void owner_is_killed()
{
        destruct(this_object());
}