
// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "移星換月" NOR; }

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;
        int level;

        if( (level = me->query_skill("douzhuan-xingyi", 1)) < 1000 )
                return notify_fail("你的鬥轉星移還不夠熟練，難以施展" + name() + "。\n" NOR);

        if( (int)query("jingli", me) < 2000 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n" NOR);

        if( (int)query("neili", me) < 5000 )
                return notify_fail("你現在內力不夠，難以施展" + name() + "。\n" NOR);

        if (query_temp("yixinghuanyue", me))
                return notify_fail("你已經運起" + name() + "。\n" NOR);

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);
        set_temp("yixinghuanyue", 1, me);
        msg = MAG "\n$N" MAG "提起真氣，默念" + name() + "心法，心中以彼之道還彼之身的法門已達發乎自然之境。\n" NOR;

        message_combatd(msg, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), level/60);

        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if ((int)query_temp("yixinghuanyue", me))
        {
                delete_temp("yixinghuanyue", me);
                tell_object(me, "你的"+name()+"運功完畢，將內力收回丹田。\n");
        }
}

