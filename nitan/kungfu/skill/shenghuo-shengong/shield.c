#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用聖火神功來提升自己的防禦力。\n");

        if ((int)query("neili", me) < 100)
                return notify_fail("你的真氣不夠。\n");

        if ((int)me->query_skill("shenghuo-shengong", 1) < 40)
                return notify_fail("你的聖火神功等級不夠。\n");

        if ((int)query_temp("shield", me))
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIG "$N" HIG "默唸聖火神功口訣，一股真氣流至奇經八脈，護住全身。\n" NOR, me);

        addn_temp("apply/armor", skill/2, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (query_temp("shield", me))
        {
                addn_temp("apply/armor", -amount, me);
                delete_temp("shield", me);
                tell_object(me, "你的聖火神功運行完畢，將內力收回丹田。\n");
        }
}
