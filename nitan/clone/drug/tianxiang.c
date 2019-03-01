// Code of ShenZhou
// tianxiang.c 天香斷續膏

#include <ansi.h>

inherit ITEM;

void setup()
{}

int cure_ob(string);
void create()
{

        set_name(MAG"天香斷續膏"NOR, ({"tian xiang", "gao"}));
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "盒");
                set("long", "這是一盒極為有效的峨嵋獨門傷藥，專治內外傷等。\n");
                set("value", 5000);
                set("no_sell", 1);
                set("medicine", 1);
                set("no_drop", "如此寶貴的靈藥丟棄了不怕回去被師父責罰嗎？");
        }

        set("used", 3);
        set("emei",1);
        setup();
}

int cure_ob(object me)
{
        if( query("eff_qi", me) == query("max_qi", me) )
                return notify_fail("你現在不用敷天香斷續膏。\n");
        
        if ( (int)me->query_condition("bonze_drug" ) > 0 )
        {
                this_player()->receive_wound("qi", 50, "用藥不當傷勢惡化死了");
                message_vision(HIR "$N敷上一些天香斷續膏，只覺傷口反而惡化，原來敷藥過急過多，藥效適得其反！\n" NOR, me);
        }
        else if ( me->query_skill_mapped("force") != "linji-zhuang" ) 
                message_vision(HIC "$N敷上一些天香斷續膏，只覺作用不大，原來內功不符，藥力行不開。\n" NOR, me);
        else
        {
                this_player()->receive_curing("qi", 500);
                message_vision(HIC "$N敷上一些天香斷續膏，只覺傷勢大為好轉，氣色好多了。\n" NOR, me);
        }

        me->apply_condition("bonze_drug", 15);

        if ( addn("used", -1) < 1 ) {
                tell_object(me, "這盒天香斷續膏用完了。\n");
                destruct(this_object());
        }
        return 1;

}
