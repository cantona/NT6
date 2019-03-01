// This program is a part of NT MudLIB
// jiuyang.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if( !query("can_exert/yijinjing/jiuyang", me) )
                return notify_fail("你還沒有領悟過少林九陽真氣呢！\n");

        if ((int)me->query_skill("yijinjing", 1) < 140)
                return notify_fail("你的易筋經修為如此之淺還想運用九陽真氣？\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("你的內力修為太差，多多打坐吧。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠。\n");

        if( query_temp("sl/jiuyang", me) )
                return notify_fail("你已經在運真氣增加攻擊力。\n");

        skill = me->query_skill("yijinjing",1);
        message_combatd(HIR"\n$N潛運少林九陽神功，體內真氣澎湃不息，全身佛光流動，寶相莊嚴！\n" NOR, me);

        addn_temp("apply/attack", skill, me);
        set_temp("sl/jiuyang", 1, me);
        addn("neili", -300, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill :), skill*2);
        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}
void remove_effect(object me, int amount)
{
        if( query_temp("sl/jiuyang", me)){
                addn_temp("apply/attack", -amount, me);
                delete_temp("sl/jiuyang", me);
                message_vision(HIY"$N將九陽真氣收回丹田，面露慈祥笑容。\n" NOR, me);
        }
}