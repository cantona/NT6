// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return "封魔"; }

void remove_effect(object me, int a_amount, int d_amount);

int perform(object me)
{
        object weapon;
        int skill;
        string msg;

        if ((int)me->query_skill("banruo-zhang", 1) < 60)
                return notify_fail("你的般若掌法不夠嫻熟，不會使用「封魔」。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，無法使用「封魔」。\n");

        if( query_temp("brz_feng", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("banruo-zhang", 1);
        msg = HIG "$N" HIG "使出般若掌「封魔」式，雙掌翻飛將周身護住。\n" NOR;
        message_combatd(msg, me);

        addn_temp("apply/attack", -skill/4, me);
        addn_temp("apply/defense", skill/3, me);
        set_temp("brz_feng", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 4, skill / 3 :), skill / 4);

        addn("neili", -100, me);
        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int a_amount, int d_amount)
{
        if( query_temp("brz_feng", me) )
        {
                addn_temp("apply/attack", a_amount, me);
                addn_temp("apply/defense", -d_amount, me);
                delete_temp("brz_feng", me);
                tell_object(me, "你的般若掌「封魔」運行完畢，將內力收回丹田。\n");
        }
}