// This program is a part of NITAN MudLIB
#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if( !target ) target = offensive_target(me);      

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("悲痛莫明只能對戰鬥中的對手使用。\n");

        if( target->is_busy() )
                return notify_fail(target->name() + "已經不能動了！\n");
                
        if( (int)me->query_skill("dabei-zhang", 1) < 100 )
                return notify_fail("你的大悲掌不夠嫻熟，不會使用「悲痛莫明」。\n");

        msg = HIB "$N臉上露出一絲悲痛的神情，和手唸了一聲阿彌陀佛,\n"NOR;
        msg += HIB "雙手緩緩的推出，看似平常的一招，可是看不出一絲\n"NOR;
        msg += HIW "破綻，次招正是大悲掌最後絕技「悲痛莫明」。\n"NOR;
        
        ap = attack_power(me, "strike");

        dp = defense_power(target, "dodge");
             
        if (ap / 2 + random(ap) > dp)
        {
                msg += HIW "$p企圖突破$N的攻擊範圍，但是被$N的掌風避的毫無退路。\n" NOR;
                target->start_busy(3 +random(4));
                addn("neili", -500, me);
        } else 
        {
                me->start_busy(2);
                addn("neili", -300, me);
                msg += HIC "$p一眼看出了$N的破綻，躲了過去。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}

