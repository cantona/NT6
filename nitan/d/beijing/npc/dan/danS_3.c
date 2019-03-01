#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(WHT"玄武"NOR+HIY"神農丹"NOR, ({"xuanwu dan", "dan"}));
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

        if( time()-query_temp("last_eat/dan(S, me)")<600 )
        {
                write("你剛服用過藥，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();

//        me->set_temp("last_eat/dan(S)", time());

        message_sort(WHT "$N" WHT "吃下一顆$n" WHT "，只覺"
                     "全身筋脈逆流而上，內力源源不斷的湧入"
                     "丹田，說不出的舒服受用。頓時感到靈台"
                     "處如湖面一般平靜，以往所學的武學知識"
                     "一一湧向心頭，在靈台處交融貫通。$N" WHT
                     "感到的經驗和潛能有了一定的進展。\n"NOR, me, this_object());
        set("jingli",query("max_jingli",  me), me);
        set("neili",query("max_neili",  me), me);
        addn("combat_exp", 200, me);
        addn("potential", 200, me);

//        me->start_busy(2);
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