// Code of ShenZhou
//  shedan.c
//  xuy 09/21/96
//  modified by ryu, 6/2/97

#include <ansi.h>
inherit ITEM;

nosave int used=0;
void delete_benefit(object me);
void decay();
int cure_ob(string);
void init()
{
        if (used) return;
        remove_call_out("decay");
        call_out("decay", 120);
}

void create()
{
        set_name("蟒蛇膽", ({"shedan", "dan" }));
        set("unit", "枚");
        set("long", "一枚深紫色的蟒蛇膽，甚是腥臭。\n");
        set("value", 20000);
                set("no_sell", 1);
        set("medicine", 1);
        set("no_cleanup", 1);
        setup();
}

int cure_ob(object me)
{
        if( !living(this_player()) ) return 0;
        if( used ) return 0;
        if( me->is_busy() )
                return notify_fail("你上一個動作還沒有完成。\n");

        if ((int)me->query_condition("bonze_drug") > 0
        || (int)me->query_condition("mang_shedan") > 0){
        addn("eff_jingli", -1, me);
        addn("max_jingli", -1, me);
        message_vision(HIR "$N吃下一顆蛇膽，只覺得頭重腳輕，搖搖欲倒，
原來服食太急太多，藥效適得其反！\n" NOR, me);
        destruct(this_object());
        return 1;
        }        

        addn("food", 10, me);
        addn("water", 10, me);
        addn_temp("apply/con", 1, me);
        addn_temp("apply/str", 1, me);
        addn("eff_jingli", 1, me);
        addn("max_jingli", 1, me);
        addn("jingli", 100, me);
        me->apply_condition("bonze_drug", 30+me->query_condition("bonze_drug"));
        me->apply_condition("mang_shedan", 30);
        set_temp("dan_effect", 1, me);
        tell_object(me, MAG"你張口輕輕一咬，蛇膽外皮便即破裂，登覺滿口苦汁，腥極苦極，幾乎要嘔將出來。\n"
                        + "可稍過片刻，你只覺呼吸順暢，耳清目明，精神爽利，力氣大增。\n"NOR);

        message("vision", MAG + me->name() + "吞下一顆蟒蛇膽，精神大旺，尤勝平時。\n"NOR, 
                        environment(me), ({me}));
//        me->start_call_out( (: call_other, __FILE__, "delete_benefit", me :), 800);
        used = 1;
//        remove_call_out("decay");
//        move(VOID_OB);
        destruct(this_object());        
        return 1;
}

void decay()
{
        object where = environment(this_object());
        if ( interactive(where) )
                message("vision", MAG"蛇膽啪的一聲破了，弄得你一身甚是腥臭。\n"NOR, 
                        where); 
        else
                message("vision", MAG"蛇膽啪的一聲破了，汁水流了一地。\n"NOR,
                        where);
        destruct(this_object());
}

/*void delete_benefit(object me)
{
        addn_temp("apply/str", -1, me);
        addn_temp("apply/con", -1, me);
        destruct(this_object());
}
*/