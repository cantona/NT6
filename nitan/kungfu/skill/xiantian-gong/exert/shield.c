// shield.c 先天無極勁

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

int exert(object me, object target)
{
        int skill;
        string msg;

        if ((int)me->query_skill("xiantian-gong", 1) < 50)
                return notify_fail("你的先天功還不夠深厚。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠。\n");

        if( query_temp("shield", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        msg = HIW "$N" HIW "深深吸了一口氣，雙臂一振，一股渾厚的氣勁登"
              "時盤旋在身邊四周。\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/armor", skill/2, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              skill / 2 :), skill);

        addn("neili", -100, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("shield", me) )
        {
                addn_temp("apply/armor", -amount, me);
                delete_temp("shield", me);
                tell_object(me, "你先天無極勁運轉完一個周天，將內力收回丹田。\n");
        }
}