// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用陰陽九轉十二重天提升自己的戰鬥力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠!");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIY "$N" HIY "雙手一合，天地元素瞬間靜止，而後瘋狂向$N" HIY "眉心湧入，周身元素飛舞，靈力逼人！\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill * 2 / 5 :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的陰陽九轉十二重天運行完畢，將內力收回丹田。\n");
        }
}
