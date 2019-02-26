#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用聖火心法來提升自己的戰鬥力。\n");

        if ((int)query("neili", me) < 150)
                return notify_fail("你的內力不夠。\n");

        if ((int)query_temp("powerup", me))
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -150, me);
        message_combatd(HIM "$N默運聖火心法，臉色先由黃翻紫，緊接着由紫翻藍，再由藍翻紅，最後又恢復為黃色，甚為詭異。\n" NOR,me);
        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/dodge", skill*2/5, me);
        addn_temp("apply/parry", skill*2/5, me);
        set_temp("powerup", 1, me);

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill * 2 / 5 :), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (query_temp("powerup", me))
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/dodge", -amount, me);
                addn_temp("apply/parry", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的聖火心法運行完畢，長長地吐了口氣，將內力收回丹田。\n");
        }
}
