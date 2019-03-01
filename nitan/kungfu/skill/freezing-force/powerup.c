// powerup.c 冰蠶寒功加力

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能提升自己的戰鬥力。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        message_combatd(HIW "$N" HIW "臉色一寒，一股煞氣騰然而起，四下登時陰風瑟瑟，冷意慘慘。\n" NOR, me);

        addn_temp("apply/attack", skill, me);
        addn_temp("apply/defense", skill, me);
        set_temp("powerup", 1, me);
        addn("neili", -100, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的冰蠶寒功運行完畢，將內力收回丹田。\n");
        }
}
