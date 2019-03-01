// Code of ShenZhou
// shanshen.c 老山三

inherit ITEM;
#include <ansi.h>
void setup()
{}

int cure_ob(string);
void create()
{
        set_name("老山參", ({"laoshan shen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "這是一株沾滿山泥的長白老山參。\n");
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
                addn("eff_jingli", -1, me);
                addn("max_jingli", -1, me);
                message_vision(HIR "$N吃下一支老山參，只覺得頭重腳輕，火氣翻騰，原來服食太多，藥效適得其反！\n" NOR, me);
                destruct(this_object());
        }
        if( random(2) == 1)
        {
        message_vision("$N吃下一株老山參，嘴裡覺得甜甜的。\n", me);
        destruct(this_object());
        return 1;
        }
        else{
                addn("eff_jingli", 1, me);
                addn("max_jingli", 1, me);
        message_vision(HIG"$N吃下一株老山參，只覺得渾身一股熱氣兜底冒了上來 !\n" NOR, me);
        }
        me->apply_condition("bonze_drug", 
        this_player()->query_condition("bonze_drug")+30);
        destruct(this_object());
        return 1;
}

