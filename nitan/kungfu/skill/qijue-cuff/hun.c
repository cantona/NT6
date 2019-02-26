// hun.c 混天七絕

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

        skill = me->query_skill("qijue-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("混天七絕只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("cuff") != "qijue-cuff") 
                return notify_fail("你沒有用七絕拳，無法使用「混天七絕」絕招！\n");

        if (me->query_skill_prepared("cuff") != "qijue-cuff")
                return notify_fail("你沒有準備使用七絕拳，無法施展「混天七絕」絕招。\n");

        if (skill < 100)
                return notify_fail("你的七絕拳等級不夠，練好了再來！\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("你必須空着雙手才能使用拳法絕招。\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIY "\n$N" HIY "滿場遊走，突然大喝一聲，$n" HIY "一驚之際，$N" HIY "雙拳揮動，\n"
              HIY "已向$n" HIY "全身上下連續擊出數拳！拳頭雨點般閃向$n。\n" NOR;
        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIW "一陣拳雨過去，$n" HIW "正待緩過氣來，不料$N" HIW "佈滿內家真力的雙拳又迎面擊來！\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIY "只聽得“咔嚓”一聲，$n" HIY "一陣劇痛，哇地一聲吐出一口" HIR "鮮血" HIY "，結結實實地被命中一拳。\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIW "$n" HIW "急運內功，全身佈滿真氣，迎着$N" HIW "的拳路，“砰砰”幾響，與$N" HIW "鬥了一個旗鼓相當！\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

