// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用易筋鍛骨內功提升自己的戰鬥力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠！");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N暗自凝神，提運九陰真氣，全身漸漸升起一層白霧。\n" NOR, me);

        addn_temp("apply/attack", skill/2, me);
        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的功力運行完畢，將內力收回丹田。\n");
        }
}