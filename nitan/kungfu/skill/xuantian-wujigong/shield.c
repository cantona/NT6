// shield.c 護體神功

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用玄天無極功來提升自己的防御力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("xuantian-wujigong", 1) < 50)
                return notify_fail("你的玄天無極功修為不夠。\n");

        if( query_temp("shield", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "大喝一聲，玄天無極真氣由體內迸發而出，頓"
                        "時一股極寒罡勁籠罩全身。\n" NOR, me);

        addn_temp("apply/armor", skill/2, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("shield", me) )
        {
                addn_temp("apply/armor", -amount, me);
                delete_temp("shield", me);
                tell_object(me, "你的玄天無極功運行完畢，將內力收回丹田。\n");
        }
}