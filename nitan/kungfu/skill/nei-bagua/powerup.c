// powerup.c 內八卦神功加力

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用內八卦神功來提升自己的戰鬥力。\n");

        if( query("neili", me)<150 )
                return notify_fail("你的內力不夠。\n");

        if( query_temp("powerup", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);
        message_combatd(HIY "$N" HIY "凝神聚氣，運起內八卦神功，真氣頓時灌滿"
                        "全身，衣衫欲裂，氣勢磅礴。\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/defense", skill/3, me);
        addn_temp("apply/parry", skill/6, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect",
                               me, skill :), skill);

        if (me->is_fighting())
                       me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/attack", -(amount/3), me);
                addn_temp("apply/defense", -(amount/3), me);
                addn_temp("apply/parry", -(amount/6), me);
                delete_temp("powerup", me);
                tell_object(me, "你的內八卦神功運行完畢，將內力收回丹田。\n");
        }
}