// reserve.c 蛤蟆功經脈倒轉

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int a_amount);

int exert(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if ((int)me->query_skill("hamagong", 1) < 80)
                return notify_fail("你的蛤蟆功不夠嫻熟，不會經脈倒轉。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠。\n");

        if( query_temp("hmg_dzjm", me) )
                return notify_fail("你已經倒轉經脈了。\n");

        skill = me->query_skill("hamagong", 1);
        msg = HIB "$N" HIB "忽地雙手撐地倒立，逆運經脈，頓時"
              "內息暗生，防御力大增。\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/dodge", skill/2, me);
        set_temp("hmg_dzjm", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 2 :), skill);

        addn("neili", -100, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("hmg_dzjm", me) )
        {
                addn_temp("apply/dodge", -amount, me);
                delete_temp("hmg_dzjm", me);
                tell_object(me, "你雙手一撐，一躍而起，將內力收回丹田。\n");
        }
}