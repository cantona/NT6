// Code of ShenZhou
// yulu-wan.c 九花玉露丸

#include <ansi.h>

inherit PILL;

void create()
{
        set_name(GRN "九花玉露丸" NOR, ({"yulu wan", "wan"}));
        set_weight(90);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "粒");
                set("long", "這是一粒九花玉露丸，發出一陣陣沁人心脾的香氣。\n");
                set("no_drop","九花玉露丸採煉不易，哪能亂扔！ \n");
                set("value", 10000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("cool_drug") > 0){
        addn("max_neili", -1, me);
        message_vision(HIR "$N吃下一粒九花玉露丸，只覺得頭重腳輕，搖搖欲倒，原來服食太急太多，藥效適得其反！\n" NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        addn("jing", 200, me);
        addn("jingli", 200, me);
        set("eff_qi",query("max_qi",  me), me);
        addn("qi", 200, me);
//        if (random(3)==1) me->add("max_neili", 3);
//        me->set("neili", (int)me->query("max_neili"));
        
        message_vision(HIG 
"$N吃下一粒九花玉露丸，一股清香之氣直透丹田，只覺得精神健旺，氣血充盈，體內真力源源滋生，將疲乏一掃而空! \n" NOR, me);

        me->apply_condition("cool_drug", 30);
        destruct(this_object());
        return 1;
}

void init()
{
        add_action("do_pour", "drop");
}

int effect_in_liquid(object ob)
{
        tell_object(this_player(),
                GRN"你只覺得體內真力源源滋生，不絕如縷。\n"NOR);
        
        addn("neili", (random(1000)+1000)/query("max_liquid", ob), this_player());
        
        if( query("neili", this_player())>query("max_neili", this_player())*3/2 )
            set("neili",query("max_neili",  this_player())*3/2, this_player());

    return 0;
}