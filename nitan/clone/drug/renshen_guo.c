// Code of ShenZhou
// renshen-guo.c 人蔘果

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "人蔘果" NOR, ({"renshen guo", "guo"}));
        set_weight(90);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", "這是一枚人蔘果，看上去就像一個白白胖胖的小娃娃。\n");
                set("value", 20000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("cool_drug") > 0){
        addn("max_neili", -1, me);
        message_vision(HIR "$N吃下一枚人蔘果，只覺得頭重腳輕，搖搖欲倒，
原來服食太急太多，藥效適得其反！\n" NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        if (random(2)==1) addn("max_neili", 2, me);
        set("neili",query("max_neili",  me), me);
        set("food", me->max_food_capacity(), me);
        set("water", me->max_water_capacity(), me);
        
        message_vision(HIG "$N吃下一枚人蔘果，只覺得精神健旺，氣血充盈，體內真力源源滋生，將疲乏飢渴一掃而空! \n" NOR, me);
        me->apply_condition("cool_drug", 30);
        destruct(this_object());
        return 1;
}
