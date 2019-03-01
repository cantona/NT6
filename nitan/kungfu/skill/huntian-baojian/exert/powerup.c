#include <ansi.h>

inherit F_CLEAN_UP;

string *force_name = ({ NOR + HIB "靛滄海", HIY "金晨曦",
                        HIR "血穹蒼", NOR + CYN "玄宇宙", }); 

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;
        string name;
        name = force_name[random(sizeof(force_name))];

        if (target != me)
                return notify_fail("你只能用渾天寶鑒來提升自己的戰鬥力。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的內力不夠。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIW "$N" HIW "微一凝神，運起渾天寶鑒之「" + name +
                        HIW "」心法，一股氣流頓將你震退數步。\n" NOR, me);

        addn_temp("apply/attack", skill/2, me);
        addn_temp("apply/defense", skill/2, me);
        set_temp("powerup", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill / 2 :), skill);

        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/defense", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "你的渾天寶鑒運行完畢，將內力收回丹田。\n");
        }
}