// 神龍再現

#include <ansi.h>

int perform(object me)
{
        int skill;
        string msg;

        if (! me->is_fighting())
                return notify_fail("龍形唱仙只能在戰鬥中使用。\n");

        if ((int)me->query_skill("hunyuan-yiqi", 1) < 150)
                return notify_fail("你的心意氣混元功不夠嫻熟，不會使用龍形唱仙。\n");

        if( query("neili", me)<300 )
                return notify_fail("你已經精疲力竭，內力不夠了。\n");

        if( query_temp("chang", me) >= 100 )
                return notify_fail("你已經叫得太久了，神龍已經厭倦了。\n");

        addn("neili", -100, me);

        message_combatd(HIR "只聽$N" HIR "口中唸唸有詞，神龍從天而將，"
                        "鑽入$N體中！\n" NOR, me);

        addn_temp("apply/attack", 1, me);
        addn_temp("apply/dodge", 1, me);
        addn_temp("apply/defense", 1, me);
                addn_temp("apply/armor", 1, me);
                addn_temp("apply/damage", 1, me);
        addn_temp("chang", 1, me);

        return 1;
}
