#include <ansi.h>

#define HUA "「" MAG "化蝶" NOR "」"

inherit F_SSERVER;

inherit F_CLEAN_UP;

void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int count, cnt, skill;

        if( userp(me) && !query("can_perform/zhuangzi-wu/hua", me) )
                return notify_fail("你還沒有學會"HUA"，不能使用這種功能。\n");

        if( query_temp("hua_die", me) )
                return notify_fail("你已經運起" HUA "了。\n");

        if ((int)me->query_skill("zhuangzi-wu", 1) < 150)
                return notify_fail("你的莊子舞等級不夠，難以施展" HUA "。\n");

        if ((int)me->query_dex() < 32)
                return notify_fail("你的身法不夠，難以施展" HUA "。\n");

        if ((int)me->query_skill("force", 1) < 150)
                return notify_fail("你的內功火候不夠，難以施展" HUA "。\n");

        if ((int)me->query_skill("dodge", 1) < 150)
                return notify_fail("你的輕功修為不夠，難以施展" HUA "。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力修為不夠，難以施展" HUA "。\n");

        if( query("neili", me)<250 )
                return notify_fail("你此時的內力不足，難以施展" HUA "。\n");

        msg = MAG "$N" MAG "一聲清嘯，身形一展，舞步宛如行雲流水、彩碟飛"
              "揚，速度變得異常敏捷。\n\n" NOR;
        
        message_combatd(msg, me, target);
        skill = me->query_skill("zhuangzi-wu", 1);
        cnt = (int)((int)me->query_condition("drunk") / 3);

        count = skill / 50;

        if (me->is_fighting())
                me->start_busy(2);

        addn_temp("dex", count, me);
        set_temp("hua_die", 1, me);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        addn("neili", -200, me);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("hua_die", me) )
        {
                addn_temp("dex", -amount, me);
                delete_temp("hua_die", me);
                tell_object(me, "你的" HUA "運行完畢，將內力收回丹田。\n");
        }
}