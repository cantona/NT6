// Code of ShenZhou
//yangrong-wan.c 人參養榮丸
//kane 1998.6
#include <ansi.h>
inherit PILL;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name(HIW"人參養榮丸"NOR, ({"yangrong wan","wan"}));
        set_weight(50);
        if (clonep())
            set_default_object(__FILE__);
    else
    {
                set("unit", "顆");
        set("long",
"一顆潔白光潤的藥丸，以人參等大補藥物煉制而成，功能理氣化虛，\n調元固本，于重傷之人更有吊命之效。\n");
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

                message_vision(BLU"$N服下一顆"+query("name")+BLU"，覺得胸口鬱悶，四肢乏力。原來服食太急\n太多，藥效適得其反！\n" NOR, me);
                destruct(this_object());
                return 1;
        }
           
        message_vision(HIW"$N服下一顆"+query("name")+HIW"，只覺全身暖融融的，說不出的受用，傷勢\n霍然而癒。\n"NOR, me);
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
            set("jingli",query("max_jingli",  me), me);
            set("eff_qi",query("max_qi",  me), me);
            set("qi",query("max_qi",  me), me);
        me->apply_condition("hot_drug",10);
        destruct(this_object());
        return 1;                
}

