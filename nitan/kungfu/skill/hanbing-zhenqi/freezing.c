#include <ansi.h>
inherit F_CLEAN_UP;

#define FRE "「" HIW "寒冰真氣" NOR "」"

void remove_effect(object me);

int exert(object me, object target)
{
        int skill;

        if( userp(me) && !query("can_perform/hanbing-zhenqi/freezing", me) )
                return notify_fail("你所學的內功中沒有這種功能。\n");

        if( query_temp("freezing", me) )
                return notify_fail("你現在正在施展" FRE "。\n");

        if (target != me)
                return notify_fail(FRE "只能對自己使用。\n");

        skill = me->query_skill("hanbing-zhenqi", 1);

        if( query("con", me)<34 )
                return notify_fail("你的先天根骨不足，無法施展" FRE "。\n");

        if (skill < 140)
                return notify_fail("你的寒冰真氣不夠，難以施展" FRE "。\n");

        if( query("max_neili", me)<2200 )
                return notify_fail("你的內力修為不足，難以施展" FRE "。\n");

        if( !query_temp("powerup", me) )
                return notify_fail("你現在尚未曾運功，難以施展" FRE "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你目前的內力不夠，難以施展" FRE "。\n");

        addn("neili", -300, me);

        message_combatd(HIW "$N" HIW "一聲冷笑，體內寒冰真氣迅速疾轉數個周"
                        "天，將力聚于掌心。\n" NOR, me);
        set_temp("freezing", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill :), skill);
        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}

void remove_effect(object me)
{
        if( query_temp("freezing", me) )
        {
                delete_temp("freezing", me);
                tell_object(me, "你的" FRE "運行完畢，將內力收回丹田。\n");
        }
}