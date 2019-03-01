// Code of ShenZhou
// jinchuang-yao.c 金創藥

#include <ansi.h>

inherit ITEM;

void setup()
{}
int cure_ob(string);
void create()
{

        set_name("金創藥", ({"jin chuangyao", "jin"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包別具靈效的少林金創藥，專治內外傷等。\n");
                set("value", 2000);
                set("no_sell", 1);
                set("no_drop", "這樣東西不能離開你。\n");
        }

        set("shaolin",1);
        setup();
}

int cure_ob(object me)
{

        if( query("eff_qi", me) == query("max_qi", me) )
                return notify_fail("你現在不需要用金創藥。\n");
        
        if ( (int)me->query_condition("bonze_drug" ) > 0 )
        {
                addn("eff_qi", -50, this_player());
                message_vision(HIR "$N敷上一些金創藥，只覺胸口煩惡欲嘔，四肢乏力，原來用得太急太多，藥效適得其反！\n" NOR, me);
        }
        else
        {
                this_player()->receive_curing("qi", 50);
                message_vision(HIC "$N小心翼翼地把一包金創藥敷在傷口上，只覺傷勢大為好轉，氣色看起來好多了。\n" NOR, me);
        }

        me->apply_condition("bonze_drug", 15);

        destruct(this_object());
        return 1;

}
