// richu.c 日月光華 之 日出東方
// By haiyan

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
    int skill;

        if( query("gender", me) != "無性" && !query("reborn/times", me))
                return notify_fail("你的性別與日月內功相斥，無法使用此絕招！\n");  

    if (target != me)
        return notify_fail("你只能用日月光華來提升自己的潛力。\n");

    if ((int)me->query_skill("riyue-guanghua",1) < 100)
        return notify_fail("你的日月光華修為太低，無法施展「日出東方」。\n");

    if( query("neili", me)<200 )
        return notify_fail("你的內力不夠。\n");

    if( query_temp("richu", me) )
        return notify_fail("你已經在運功中了。\n");

    skill = me->query_skill("force");
    addn("neili", -120, me);
    me->receive_damage("qi", 0);
    message_combatd(HIR "$N" HIR "一聲怪嘯，雙目變得赤紅，雙足一點，身子騰空而起，"
                    "四周頓時熱浪翻湧，灸熱難當。\n" NOR, me);
    addn_temp("apply/attack", skill/3, me);
    addn_temp("apply/dodge", skill/3, me);
    addn_temp("apply/parry", skill/3, me);
    addn_temp("apply/damage", skill*3, me);
    addn_temp("apply/dex", skill/20, me);

    set_temp("richu", 1, me);

    me->start_call_out((:call_other, __FILE__, "remove_effect", me,
                         skill:), skill);
    if (me->is_fighting()) me->start_busy(3);

    return 1;
}

void remove_effect(object me, int amount)
{
    if( query_temp("richu", me) )
    {
        addn_temp("apply/attack", -amount/3, me);
        addn_temp("apply/dodge", -amount/3, me);
        addn_temp("apply/parry", -amount/3, me);
        addn_temp("apply/damage", -amount*3, me);
        addn_temp("apply/dex", -amount/20, me);
        delete_temp("richu", me);
        tell_object(me, "你的日出東方運行完畢，將內力收回丹田。\n");
    }
}
