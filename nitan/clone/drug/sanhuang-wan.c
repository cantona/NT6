// Code of ShenZhou
//sanhuang-wan.c
//kane 1998.6
// xQin 04/01

#include <ansi.h>
inherit PILL;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name(HIY"三黃寶蠟丸"NOR, ({"sanhuang wan","wan"}));
        set_weight(50);
        if (clonep())
            set_default_object(__FILE__);
    else
    {
        set("unit", "顆");
        set("no_sell",1);
        set("no_get",1);
        set("no_drop",1);
        set("long",
"一顆黃澄澄的藥丸，由牛黃、雄黃、雌黃這三黃為主，輔以其它藥物\n煉製而成，是武當派療傷、療毒的靈藥。對蟲毒有奇效。\n");
                set("value", 20000);
                set("medicine", 1);
    }
        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("hot_drug") > 0)
        {
               if( query("neili", me)>500 )
                       addn("neili", -500, me);
                else
                        addn("neili", -(query("neili", me)), me);

                message_vision(BLU"$N服下一顆"+query("name")+BLU"，覺得體內真氣逆行，內力大損。原來服食\n太急太多，藥效適得其反！\n" NOR, me);
        destruct(this_object());
        return 1;
        }
           
        message_vision(HIM"$N服下一顆"+query("name")+HIM"，只覺通體舒泰，精神煥發，傷勢大有好轉。\n"NOR, me);
        me->receive_heal("qi", 400+random(200));
        me->apply_condition("hot_drug", 15);

        if ((int)me->query_condition("insect_poison") )
        {
        me->apply_condition("insect_poison", 0);
        }
        destruct(this_object());
           return 1;
}

