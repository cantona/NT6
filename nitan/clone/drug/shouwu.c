// Code of ShenZhou
// shouwu.c 何首烏

inherit ITEM;
#include <ansi.h>

void setup()
{}
int cure_ob(string);
void create()
{
        set_name("何首烏", ({"heshou wu", "wu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "棵");
                set("long", "這是一棵初具人形的何首烏。\n");
                set("value", 10000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        if ( (int)me->query_condition("bonze_drug" ) > 0 )
        {
                addn("max_neili", -1, me);
                me->apply_condition("bonze_drug", 30);
                message_vision(HIR "$N吃下一支何首烏，只覺得頭重腳輕，火氣翻騰，原來服食太多，藥效適得其反！\n" NOR, me);
                destruct(this_object());
        }
        if( random(2) == 1)
        {
        message_vision("$N吃下一棵何首烏，嘴裡覺得甜甜的。\n", me);
        destruct(this_object());
        return 1;
        }
        else
        {
        addn("max_neili", 1, me);
        message_vision(HIG"$N吃下一棵何首烏，頓時間覺得全身充滿了活力 !\n"NOR, me);
        }
        me->apply_condition("bonze_drug", 
        this_player()->query_condition("bonze_drug")+30);
        destruct(this_object());
        return 1;
}
