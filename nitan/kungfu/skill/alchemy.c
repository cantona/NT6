// alchemy.c
#include <ansi.h>

inherit SKILL;

//string type() { return "technic"; }
string type() { return "knowledge"; } 

int valid_learn(object me)
{
        return 1;
}

void skill_improved(object me) 
{
        int level;

        level = me->query_skillo("linghun-zhili", 1);
        if( me->query_skillo("alchemy", 1) > 2399 && level < 1000 )
        {
                tell_object(me, HIM "由於靈魂之力未達到靈境，無法藉助靈氣之力，你的煉丹技藝無法提升。\n" NOR); 
                return;
        }

        if( me->query_skillo("alchemy", 1) > 2699 && level < 2000 )
        {
                tell_object(me, HIM "由於靈魂之力未達到神境，無法藉助神之力，你的煉丹技藝無法提升。\n" NOR); 
                return;
        }

        if( me->query_skillo("alchemy", 1) > 2999 && level < 3000 )
        {
                tell_object(me, HIM "由於靈魂之力未達到天境，無法藉助天地之力，你的煉丹技藝無法提升。\n" NOR); 
                return;
        }
}
