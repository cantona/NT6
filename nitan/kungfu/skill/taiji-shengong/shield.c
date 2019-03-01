// shield.c 太極護體神功
// Created by Lonely

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用太極神功來提升自己的防御力。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠。\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 40)
                return notify_fail("你的太極神功等級不夠。\n");

        if( query_temp("shield", me) )
                return notify_fail("你已經在運功中了。\n");

        skill = me->query_skill("force");
        addn("neili", -100, me);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "默念太極神功的口訣：他"
                            "強由他強，清風拂山岡。他橫任他橫，"
                            "明月照大江……\n剎那間只見$N" 
                        HIR "全身頓時浮現出一層剛猛的勁氣，將$P"
                        HIR "全全籠罩。\n" NOR, me);

        addn_temp("apply/armor", skill/2, me);
        set_temp("shield", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect", 
                           me, skill / 2 :), skill);

        if (me->is_fighting()) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("shield", me) )
        {
                addn_temp("apply/armor", -amount, me);
                delete_temp("shield", me);
                tell_object(me, "你的太極神功運行完畢，將內力收回丹田。\n");
        }
}

