// poqizhen.c 破氣針
 
#include <ansi.h>
 
inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp, neili_wound, qi_wound;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("shigu-bifa",1);

        if( !(me->is_fighting() ))
                return notify_fail("「制氣」只能在戰鬥中用在對手身上。\n");
 
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "dagger" )
                return notify_fail("你使用的武器不對。\n");

        if( skill < 80)
                return notify_fail("你的子母針法不夠純熟, 不能使用「」！\n");

        if( query("neili", me)<150 )
                return notify_fail("你的內力不夠，無法運用「制氣」！\n");
 
        msg = HIR "$N大筆一起，向$n丹田連點三點，正是那“裴”字的起首三筆，自上而下的劃將下來。\n";
        message_vision(msg, me, target);
 
        ap = me->query_skill("dagger") + skill;
        dp = target->query_skill("force") / 3;
        if( dp < 1 )
                dp = 1;
        if( random(ap) > dp )
        {
                if(userp(me))
                        addn("neili", -100, me);
                msg = HIR"$N筆尖絲毫不差的點中對方要害, $n頓時覺得丹田上一陣刺痛，\n";
                msg += HIR"全身真氣狂泄而出！\n" NOR;

                neili_wound = 1000 + random(skill);
                if( neili_wound>query("neili", target) )
                        neili_wound=query("neili", target);

                qi_wound = neili_wound / 5;
                if( qi_wound>query("qi", target) )
                        qi_wound=query("qi", target);
                if(qi_wound < 0) qi_wound = 0;

                addn("neili", -neili_wound, target);
                addn("qi", -qi_wound, target);
                addn("eff_qi", -qi_wound, target);
                target->start_busy(3);me->start_perform( 4+random(3), "「制氣」");
}
        else
        {
                if(userp(me))
                        addn("neili", -80, me);
                msg = HIW"可是$n瞬間反應過來，騰挪跳躍，躲過了這次重創。\n"NOR;
                me->start_busy(2);
        }
        message_vision(msg, me, target);

        return 1;
}