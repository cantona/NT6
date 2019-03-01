// Code of ShenZhou
// wuchang-dan.c 無常丹

#include <ansi.h>

inherit ITEM;

int cure_ob(string);

void create()
{
        set_name(HIR "無常丹" NOR, ({"wuchang dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是桃花島療傷聖藥無常丹。\n");
                set("value", 5000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        if ( (int)this_player()->query_condition("bonze_drug" ) > 0 )
        {
                addn("neili", -100, this_player());
                message_vision(HIR "$N吃下一棵無常丹，只覺得頭重腳輕，火氣翻騰，
原來服食太多，藥效適得其反！\n" NOR, this_player());
                this_player()->apply_condition("bonze_drug",
                this_player()->query_condition("bonze_drug")+10);
                destruct(this_object());
        }
        set("eff_qi",query("max_qi",  me), me);

        message_vision(HIG 
"$N吃下一粒無常丹，頓時神完氣足，精神煥發\n" NOR, me);
        this_player()->apply_condition("bonze_drug",
                this_player()->query_condition("bonze_drug")+10);

        destruct(this_object());
        return 1;
}
