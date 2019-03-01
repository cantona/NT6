// This program is a part of NT MudLIB
// powerup.c 九陽神功加力

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用九陽神功來提升自己的戰鬥力。\n");

        if ((int)query("neili", me) < 100)
                return notify_fail("你的內力不夠。\n");

        if ((int)query_temp("powerup", me))
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "微一凝神，運起九陽神功，將真氣"
                        "凝聚在丹田之中，沿奇經八脈遍布全身！\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/unarmed_damage", skill*2/5, me);
        addn_temp("apply/damage", skill*2/5, me);
        addn_temp("apply/parry", skill/3, me);
        addn_temp("apply/dodge", skill/3, me);
        if( query("reborn/times", me) )
                addn_temp("apply/dispel_poison", skill, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)query_temp("powerup", me))
        {
                addn_temp("apply/attack", -(amount*2/5), me);
                addn_temp("apply/unarmed_damage", -(amount*2/5), me);
                addn_temp("apply/damage", -(amount*2/5), me);
                addn_temp("apply/parry", -(amount/3), me);
                addn_temp("apply/dodge", -(amount/3), me);
                if( query("reborn/times", me) )
                        addn_temp("apply/dispel_poison", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的九陽神功運行完畢，將內力收回丹田。\n");
        }
}
