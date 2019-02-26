// hun.c 凝雪神功

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("mingyu-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("凝雪神功只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("cuff") != "mingyu-cuff") 
                return notify_fail("你沒有用明玉拳，無法使用「凝雪神功」絕招！\n");

        if (me->query_skill_prepared("cuff") != "mingyu-cuff")
                return notify_fail("你沒有準備使用明玉拳，無法施展「凝雪神功」絕招。\n");

        if (skill < 100)
                return notify_fail("你的明玉拳等級不夠，練好了再來！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必須空着雙手才能使用掌法絕招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIW "\n$N" HIW "默運運起明玉拳法的" HIC "凝雪神功" HIW "，忽的長嘯一聲，大喝一聲“雪海茫茫~~~~~”\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIW "\n緊接着地面上響起了一陣輕而密的劈啪之聲，眼看着巖石以及泥土的表面上，\n"
              HIW "瞬時凝結起了寸餘高的冰塊。“唰”地一下，向$n襲來。\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIW "$n" HIW "躲閃不急，慘叫一聲，直挺挺地被凍僵了。\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIC "$n" HIC "見勢不妙，猛地向後一躍，躲開了飛來的冰塊。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

