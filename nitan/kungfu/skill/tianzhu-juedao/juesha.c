// tie@fengyun
#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;
int perform(object me, object target)
{
        string msg;
        int extra;
        object weapon;
        extra = me->query_skill("tianzhu-juedao",1);

        if ( extra < 150) return notify_fail("你的天竺絕刀還不夠純熟！\n");

        if( !target ) target = offensive_target(me);
        if( !target ||        !me->is_fighting(target) )
                return notify_fail("［天竺絕殺］只能對戰鬥中的對手使用。\n");


        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "blade" )
            return notify_fail("你使用的武器不對。\n");

        if (me->query_skill_mapped("blade") != "tianzhu-juedao")
                return notify_fail("你還沒有準備天竺絕刀！\n");

        if( query("max_neili", me)<1600 )
                return notify_fail("你內力修為不足！\n");
        if( query("neili", me)<600 )
                return notify_fail("你內力不夠！\n");

        weapon=query_temp("weapon", me);
        addn("neili", -400, me);
        addn("jingli", -100, me);
        msg = HIY  "$N使出天竺絕刀中的［天竺絕殺］，一招連環三式，手中的"+ 
                  weapon->name()+ HIY"閃電般向$n攻出！\n"
                  "第一刀！" NOR;
        message_vision(msg,me,target);
        addn_temp("apply/damage", 200, me);
        addn_temp("apply/attack", 400, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        msg = HIY  "第二刀！" NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        msg = HIY  "第三刀！" NOR;
        message_vision(msg,me,target);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),TYPE_REGULAR,msg);
        me->start_busy(3);
        addn_temp("apply/damage", -200, me);
        addn_temp("apply/attack", -400, me);
        return 1;
}