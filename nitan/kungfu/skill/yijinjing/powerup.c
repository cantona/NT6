// powerup.c 易筋經加力

#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( target != me )
                return notify_fail("你只能提升自己的戰鬥力。\n");
        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠。\n");
        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        message_combatd(
                HIR "$N舌尖一咬，噴出一口鮮血，運起易筋經神功已將全身潛力盡數提起！\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        set_temp("powerup", 1, me);
        addn("neili", -100, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill * 2 / 5 :), skill);

        if( me->is_fighting() ) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/defense", -amount, me);
        delete_temp("powerup", me);
        tell_object(me, "你的易筋經神功運行完畢，將內力收回丹田。\n");
}