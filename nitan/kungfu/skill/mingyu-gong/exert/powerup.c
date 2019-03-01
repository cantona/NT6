// powerup.c 明玉功加力

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用明玉功來提升自己的戰鬥力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "運起玉明功，全身皮膚瞬間變得晶瑩無比，光滑異常，整個人\n"
                        "神聖而不可侵犯，散發著令人心顫的寒氣。\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/parry", skill/3, me);
        addn_temp("apply/dodge", skill/3, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -(amount*2/5), me);
                addn_temp("apply/parry", -(amount/3), me);
                addn_temp("apply/dodge", -(amount/3), me);
                delete_temp("powerup", me);
                tell_object(me, "你的明玉功運行完畢，將內力收回丹田。\n");
        }
}
