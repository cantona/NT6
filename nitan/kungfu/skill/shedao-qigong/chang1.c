// 唱仙法

#include <ansi.h>

string name() { return "唱字決"; }

int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("唱仙法只能在戰鬥中使用。\n");

        if ((int)me->query_skill("shedao-qigong", 1) < 60)
                return notify_fail("你的蛇島奇功不夠嫻熟，不會使用唱仙法。\n");

        if( query("neili", me)<300 )
                return notify_fail("你已經唱得精疲力竭，內力不夠了。\n");

        if( query_temp("chang", me) >= 30 )
                return notify_fail("你已經唱得太久了，不能再唱了。\n");

        skill = me->query_skill("force");

        addn("neili", -200, me);

        message_combatd(HIR "只聽$N" HIR "口中念念有詞，頃刻"
                        "之間武功大進！\n" NOR, me);

        addn_temp("apply/attack", 10, me);
        addn_temp("apply/dodge", 10, me);
        addn_temp("apply/force", 10, me);
        addn_temp("apply/defense", 10, me);
        addn_temp("chang", 1, me);

        return 1;
}