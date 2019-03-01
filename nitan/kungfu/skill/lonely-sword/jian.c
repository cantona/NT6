#include <ansi.h>

string name() { return MAG "劍心通明" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int skill;

        if( !query("reborn/times", me) )
                return notify_fail("你所使用的外功中沒有這個功能。\n");

        if (me->query_skill_mapped("sword") != "lonely-sword")
                return notify_fail("你還沒有激發獨孤九劍。\n");

        if( !query("lonely-sword/nothing", me) )
                return notify_fail("你還沒有進入無招境界，何談劍心通明？\n");

        if ((int)me->query_skill("lonely-sword", 1) < 1000)
                return notify_fail("你的獨孤九劍等級不夠，難以施展" + name() + "。\n");

        if( query_temp("dugu_sword", me) )
                return notify_fail("你已經運起" + name() + "了。\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你所使用的武器不對！\n");

        if( query("skill_type", weapon) != "sword" )
                return notify_fail("你所使用的武器不對！\n");

        if( query("neili", me)<250 )
                return notify_fail("你此時的內力不足，難以施展" + name() + "。\n");

        msg = MAG "$N" MAG "凝神聚氣，揮洒手中兵器，進入無招無我，劍心通明境界！\n\n" NOR;

        message_combatd(msg, me, target);

        if (me->is_fighting())
                me->start_busy(1);

        skill = me->query_skill("lonely-sword", 1);

        addn_temp("apply/damage", skill*2, me);
        set_temp("dugu_sword", 1, me);

        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, skill * 2 :), 180);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("dugu_sword", me) )
        {
                addn_temp("apply/damage", -1*amount, me);
                delete_temp("dugu_sword", me);
                tell_object(me, "你的" + name() + "運行完畢，將內力收回丹田。\n");
        }
}
