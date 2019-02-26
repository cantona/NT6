// dan.c 腰斬

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("「腰斬」只能對戰鬥中的對手使用。\n");
 
        if(me->query_skill_mapped("cuff") != "mizong-cuff") 
                return notify_fail("你沒有用迷蹤拳，無法使用「腰斬」絕招！\n");

        if (me->query_skill_prepared("cuff") != "mizong-cuff")
                return notify_fail("你沒有準備使用迷蹤拳，無法施展「腰斬」絕招。\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必須空着雙手才能使用掌法絕招。\n");

        if ((int)me->query_skill("mizong-cuff", 1) < 200)
                return notify_fail("你的迷蹤拳不夠嫻熟，不會使用「腰斬」。\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功修為不夠高。\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("你現在內力太弱，不能使用「腰斬」。\n");
                        
        msg = HIR "\n$N" HIR "突然繞到$n" HIR "身後，雙拳猛的擊向$n" HIR "的後腰！\n" NOR;

        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);
        
        damage = ap*2 + random(ap);
        damage+=query("jiali", me);

        if (living(target))
                dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
        else
                dp = 0;

        dp = dp*3/2;

        weapon2=query_temp("weapon", target);
        
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -damage/2, me);

                msg += HIR "只聽“咔嚓”一聲悶響！$n" HIR "噴出一口鮮血，軟塌塌的倒了下去！\n" NOR;
                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else 
        {
                msg += HIB "哪知$n" HIB "早就有所準備，身形一展，輕易的化解了這招！\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}