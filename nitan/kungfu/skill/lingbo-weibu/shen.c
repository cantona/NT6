// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return MAG "神光離合" NOR; }

void remove_effect(object me);

int perform(object me, object target)
{
        string msg;

        if( !query("reborn/times", me) )
                return notify_fail("你尚未轉世重生，無法施展" + name() + "。\n" NOR);

        if( me->query_skill("lingbo-weibu", 1) < 1000 )
                return notify_fail("你的凌波微步還不夠熟練，難以施展" + name() + "。\n" NOR);

        if( query("jingli", me)<2000 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n" NOR);

        if( query("neili", me)<5000 )
                return notify_fail("你現在內力不夠，難以施展" + name() + "。\n" NOR);

        if( query_temp("immortal", me) )
                return notify_fail("你已經運起" + name() + "。\n" NOR);

        if( time() - query_temp("last_immortal", me) < 20 )
                return notify_fail("你無法連續無限制的使用" + name() + "。\n" NOR);

        addn("neili", -1000, me);
        me->receive_damage("qi", 0);
        set_temp("immortal", 1, me);

        msg = MAG "\n$N" MAG "提起真氣，施展" + name() + "，身形虛晃，神光交錯，離合難分，讓人難以看清所在。\n" NOR;

        message_combatd(msg, me);
        set_temp("last_immortal", time(), me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me :), 30);

        if( me->is_fighting() ) me->start_busy(2);
        return 1;

}

void remove_effect(object me)
{
        if( query_temp("immortal", me) )
        {
                delete_temp("immortal", me);
                tell_object(me, "你的「神光離合」運功完畢，將內力收回丹田。\n");
        }
}
