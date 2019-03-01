// Code of ShenZhou
//heishi-dan.c
//kane 1998.5
#include <ansi.h>
inherit PILL;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name(BLU"玉洞黑石丹"NOR, ({"yudong dan", "heishi dan", "dan"}));
        set_weight(50);
        if (clonep())
            set_default_object(__FILE__);
    else 
    {
                set("unit", "顆");
        set("long", "黑黑的一顆藥丸，毫不起眼，卻是崆峒派的療傷聖藥。\n");
                set("value", 20000);
                set("no_sell", 1);
                set("medicine", 1);
    }
        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("hot_drug") > 0)
        {
                if( query("neili", me)>500 )
                {
                        addn("neili", -500, me);
                }
                        else
                        {
                                addn("neili", -(query("neili", me)), me);
                        }        
                message_vision(BLU"$N服下一顆黑石玉洞丹，覺得體內真氣翻湧，內力大損。原來服食太急太多，藥效適得其反！\n" NOR, me);
                destruct(this_object());
                return 1;
        }
        message_vision(BLU"$N服下一顆黑石玉洞丹，只覺三焦通暢，五氣調和，內外傷都大有好轉。\n"NOR, me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
                me->apply_condition("hot_drug", 20);

        if ((((int)me->query_condition("qs_damage")) > 0) && (((int)me->query_condition("qs_damage")) < 30))
                me->apply_condition("qs_damage",0);
                  else
                          me->apply_condition("qs_damage",(int)me->query_condition("qs_damage")-30);
                destruct(this_object());
            return 1;
}
