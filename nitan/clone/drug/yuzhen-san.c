// Code of ShenZhou
//yuzhen-san.c
//kane 1998.5
#include <ansi.h>
inherit PILL;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name(HIC"玉真散"NOR, ({"yuzhen san", "san"}));
        set_weight(80);
        if (clonep())
            set_default_object(__FILE__);
    else 
    {
                set("unit", "包");
        set("long", "玉真散是華山派的療傷靈藥，可解紫霞功所造成的傷。\n");
                set("value", 8000);
                set("no_sell", 1);
                set("medicine", 1);
    }
        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("hot_drug") > 0)
        {
        addn("qi", -300, me);
        message_vision(BLU"$N服下一包玉真散，覺得胸口悶惡難當，如中重錘。原來服食太急太多，藥效適得其反！\n" NOR, me);
        destruct(this_object());
        return 1;
        }
        
   
        message_vision(HIY"$N服下一包玉真散，只覺四體通泰，傷勢大大好轉。\n"NOR, me);

        me->receive_curing("qi",500);            
        me->apply_condition("hot_drug", 15);

        if ((((int)me->query_condition("hyz_damage")) > 0) && 
(((int)me->query_condition("hyz_damage")) < 30))
                me->apply_condition("hyz_damage",0);
        else
                  
me->apply_condition("hyz_damage",(int)me->query_condition("hyz_damage")-30);
        destruct(this_object());
   return 1;
}
