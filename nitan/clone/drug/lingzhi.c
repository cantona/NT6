// Code of ShenZhou
//lingzhi.c

#include <ansi.h>

inherit ITEM;

int cure_ob(string);
void init();

void create()
{
        set_name(HIW "靈芝" NOR, ({"ling zhi", "zhi"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", HIW"這是一枚靈芝，長約四寸，如傘狀，通體晶白。\n"NOR);
                set("value", 20000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("cool_drug") > 0){
        addn("max_jingli", -1, me);
        addn("eff_jingli", -1, me);
        message_vision(HIR "$N吃下一枚靈芝，只覺得頭重腳輕，搖搖欲倒，原來服食太急太多，藥效適得其反！\n" NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("qi",query("max_qi",  me), me);
        set("neili",query("max_neili",  me), me);
        
        message_vision(HIG "$N吃下一枚靈芝，只覺得精神健旺，氣血充盈，體內真力源源滋生，甚至不再感到飢餓乾渴! \n" NOR, me);

        me->apply_condition("cool_drug", 30);
        destruct(this_object());
        return 1;
}