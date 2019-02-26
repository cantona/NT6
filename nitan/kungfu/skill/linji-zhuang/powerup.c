// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int di);

int exert(object me, object target)
{
        int skill;
        int di;
        object weapon;

        if (target != me)
                return notify_fail("你只能用臨濟莊提升自己的戰鬥力。\n");

        if ((int)query("neili", me) < 100)
                return notify_fail("你的內力不夠。\n");

        if ((int)query_temp("powerup", me))
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        if (query("sex", me)) di = 0; else di = skill / 2;
        if (di > 1000) di = 1000;

        message_combatd(MAG "$N" MAG "微一凝神，運起臨濟莊，一聲嬌喝，"
                        "四周的空氣彷彿都凝固了！\n" NOR, me);

        if (objectp(weapon = query_temp("weapon", me)))
        {
                if (di >= 95)
                        message_combatd(HIR "$N" HIR "臉色一沉，運起臨濟莊神通，霎時間" +
                                        weapon->name() + HIR "光華四射，漫起無邊殺意。\n" NOR, me);
                else
                if (di >= 80)
                        message_combatd(HIR "$N" HIR "潛運內力，只見" +
                                        weapon->name() + HIR "閃過一道光華，氣勢攝人，令人肅穆。\n" NOR, me);
                else
                if (di >= 30)
                        message_combatd(HIR "$N" HIR "默運內力，就見那" +
                                        weapon->name() + HIR "隱隱透出一股光芒，閃爍不定。\n" NOR, me);
        }

        addn_temp("apply/attack", skill / 3, me);
        addn_temp("apply/dodge", skill / 3, me);
        addn_temp("apply/damage", di, me);
        addn_temp("apply/unarmed_damage", di, me);
        set_temp("powerup", 1, me);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill / 3, di :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount, int di)
{
        if (query_temp("powerup", me))
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/dodge", -amount, me);
                addn_temp("apply/damage", -di, me);
                addn_temp("apply/unarmed_damage", -di, me);
                delete_temp("powerup", me);
                tell_object(me, "你的臨濟莊運行完畢，將內力收回丹田。\n");
        }
}
