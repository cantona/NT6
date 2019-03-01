// freeze.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用冷月神功提升自己的戰鬥力。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠！");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "全身關節“格啦格啦”一陣爆響，一股至陰的內勁從渾身經脈迸發出來。\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        addn_temp("apply/damage", skill*5, me);
        addn_temp("apply/unarmed_damage", skill*5, me);
        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 3 :), skill);

        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                addn_temp("apply/damage", -amount*15, me);
                addn_temp("apply/unarmed_damage", -amount*15, me);
                delete_temp("powerup", me);
                tell_object(me, "你的冷月神功運行完畢，將內力收回丹田。\n");
        }
}
