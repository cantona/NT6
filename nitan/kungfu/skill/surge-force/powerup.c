// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用怒濤潮湧提升自己的戰鬥力。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -200, me);
        me->receive_damage("qi", 0);

        message_combatd(HIC "$N" HIC"一聲長嘯，激起一陣狂風，氣"
                        "浪翻翻滾滾，向兩旁散開。\n霎時之間，便"
                        "似長風動起，氣雲聚合，天地渺然，有如海"
                        "浪滔滔。\n" NOR, me);

        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/unarmed_damage", skill*4, me);
        set_temp("powerup", 1, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -(skill*2/5), me);
                addn_temp("apply/defense", -(skill*2/5), me);
                addn_temp("apply/unarmed_damage", -(skill*4), me);
                delete_temp("powerup", me);
                tell_object(me, "你的怒濤潮湧運行完畢，將內力收回丹田。\n");
        }
}