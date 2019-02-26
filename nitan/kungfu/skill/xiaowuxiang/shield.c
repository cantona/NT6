// This program is a part of NITAN MudLIB
// shield.c 護體神功

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( target != me ) 
                return notify_fail("你只能用小無相功來運護體神功。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠。\n");
        if( query_temp("shield", me) )
                return notify_fail("你已經在運功\中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(
        MAG "$N長吸一口氣，運起護體神功，身上衣衫緩緩漲起。ⅵ\n" NOR, me);

        addn_temp("apply/armor", skill/2, me);
        // me->addn_temp("apply/defense",  skill / 2);
        set_temp("shield", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill/2 :), skill/2);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        addn_temp("apply/armor", -amount, me);
        // me->addn_temp("apply/defense", - amount);
        delete_temp("shield", me);
        tell_object(me, "你的護體神功運行完畢，將內力收回丹田。\n");
}
