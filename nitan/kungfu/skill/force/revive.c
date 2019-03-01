// revive.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
//inherit SSERVER;

int exert(object me, object target)
{
        int n, t;

        if (me != target)
                return notify_fail("你只能用內功恢復自己的體力。\n");

        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠。\n");

        t=query("max_tili", me)-query("tili", me);
        if (t < 10)
                return notify_fail("你現在體力充沛。\n");
        n = me->query_skill("force");
        if (n < 20) n = 20;
        if( query("neili", me)<n)n=query("neili", me);

        addn("neili", -n, me);
        addn("tili", (n/10), me);
        if( query("tili", me)>query("max_tili", me) )
                set("tili",query("max_tili",  me), me);
        
        message_combatd("$N吸了口氣，丹田真氣遊走四肢，全身也漸漸有了力氣。\n", me);

        if( me->is_fighting() ) me->start_busy(1);
        
        return 1;
}
int help(object me)
{
        write(WHT"\n基本內功之補充體力："NOR"\n");
        write(@HELP

        使用功效：
                補充自己消耗的體力　

        出手要求：
                基本內功
                內力20
HELP
        );
        return 1;
}
