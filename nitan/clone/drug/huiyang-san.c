// Code of ShenZhou
//huiyang-san.c 回陽五龍散
//kane 1998.6
#include <ansi.h>
inherit PILL;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name(HIY"回陽五龍散"NOR, ({"huiyang san","san"}));
        set_weight(50);
        if (clonep())
            set_default_object(__FILE__);
    else
    {
                set("unit", "包");
        set("long", 
"崆峒派常用的療傷靈藥。粉末微細，色澤淡黃，微有辛辣刺鼻的味道\n
，對水沖服效果尤佳。\n");
                set("value", 10000);
                set("medicine", 1);
                set("no_sell", 1);
    }
        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("hot_drug") > 0)
        {
                if( query("jingli", me)>500 )
                        addn("jingli", -500, me);
                else
                        addn("jingli", -(query("jingli", me)), me);

                message_vision(BLU"$N服下一包"+query("name")+BLU"，覺得胸口鬱悶，四肢乏力。原來服食太急\n太多，藥效適得其反！\n" NOR, me);
                destruct(this_object());
                return 1;
        }
           
        message_vision(HIY"$N服下一包"+query("name")+HIY"，只覺通體舒泰，精神煥發，傷勢大有好轉。\n"NOR, me);
        me->receive_heal("qi", 100+random(200));
        addn("jingli", 100+random(200), me);
        me->apply_condition("hot_drug", 30);

        if ((int)me->query_condition("snake_poison") > 0)         
                    me->apply_condition("snake_poison",0);
          destruct(this_object());
           return 1;
}

void init()
{
        add_action("do_pour", "pour");
}

int effect_in_liquid(object ob)
{

        tell_object(this_player(),HIG"你只覺得體內一股暖氣流動，大為受用。\n"NOR);
        this_player()->receive_heal("qi",10+random(20));
       return 0;
}

