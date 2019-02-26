// hun.c 雙龍搶珠

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;
        string *limbs,limb;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("mizong-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("雙龍搶珠只能對戰鬥中的對手使用。\n");

        if(me->query_skill_mapped("cuff") != "mizong-cuff") 
                return notify_fail("你沒有用迷蹤拳，無法使用雙龍搶珠絕招！\n");

        if( me->query_skill_prepared("cuff") != "mizong-cuff" ) 
                return notify_fail("你所備的並非迷蹤拳，不能使用雙龍搶珠絕招！\n"); 

        if (skill < 100)
                return notify_fail("你的迷蹤拳等級不夠，練好了再來！\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你拿着武器如何使用拳法絕招？\n");

        if( query("neili", me)<500 )
                return notify_fail("你的內力不夠。\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIY "$N" HIY "身形飄忽，拳影四面八方向$n" HIY "籠罩而去！\n\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        msg = HIR "\n$N" HIR "雙拳宛若佈下天羅地網，招招擊向$n" HIR "的關節要害！\n" NOR;
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                limbs=query("limbs", target);
                limb = limbs[random(sizeof(limbs))];
                msg += HIB "$n" HIB "大驚失色，連連中招，竟被$N" HIB "擊中" + limb + "！\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIY "$n" HIY "不退反進，長袖一圈一帶，$N" HIY "竟遞不進招去。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

