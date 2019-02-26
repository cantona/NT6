// powerup.c 太玄神功加力
// By haiyan

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用太玄神功來提升自己的戰鬥力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("taixuan-shengong", 1) < 100)
                return notify_fail("你對太玄神功的理解還太膚淺。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "微一凝神，運起太玄神功，只聽$P"
                        "全身骨骼噼噼啪啪一陣爆響，渾身充滿活力！\n" NOR, me);

        addn_temp("apply/attack", skill*27/50, me);
        addn_temp("apply/parry", skill*27/50, me);
        addn_temp("apply/dodge", skill*27/50, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill * 27 / 50 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/parry", -amount, me);
                addn_temp("apply/dodge", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的太玄神功運行完畢，將內力收回丹田。\n");
        }
}
