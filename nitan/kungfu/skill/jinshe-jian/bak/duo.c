// This program is a part of NITAN MudLIB
// duo.c  金蛇劍法  (奪魄)

#include <ansi.h>
inherit F_SSERVER;

void end(object target, int damage);

int perform(object me, object target)
{
        int damage, ap, dp;
        string msg;
        
        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() )
                return notify_fail("奪魄只能對同地方的對手使用。\n");
        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("奪魄只能對戰鬥中的對手使用。\n");
                
        if( (int)me->query_skill("jinshe-jian", 1) < 100 )
                return notify_fail("你的金蛇劍法不夠嫻熟，不會使用「奪魄」。\n");
                
        if( query("neili", me)<200 )
                return notify_fail("你現在內力太弱，不能使出奪魄。\n");
                
        if( query_temp("sword", target) == 1 )
                return notify_fail(query("name", target)+"正在魂飛魄散間，快放手攻擊啊!\n");
                
        msg = HIW "$N突然眼中金芒大盛，一股寒意破空直襲$n。\n"NOR;
        addn("neili", -400, me);
        me->start_busy(1);
        
        ap=me->query_skill("sword")*3/2+query("level", me)*20+
             me->query_skill("martial-cognize", 1);
        dp=target->query_skill("dodge")+query("level", target)*20+
             target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                msg += WHT"$p被嚇得魂飛魄散，只見對方攻勢大盛，越戰越勇。\n"NOR;
                if (! target->is_busy())
                target->start_busy(3);
                addn("neili", -100, me);
                damage = me->query_skill("jinshe-jian",1);
                damage = 0-damage/8-random(damage/8);
                
                if( !query_temp("apply/attack", target) )
                    set_temp("apply/attack", damage, target);
                else
                    addn_temp("apply/attack", damage, target);
                if( !query_temp("apply/defense", target) )
                    set_temp("apply/defense", damage, target);
                else
                    addn_temp("apply/defense", damage, target);
                set_temp("sword", 1, target);
                call_out("end", 30, target, damage);
        }
        else
        {
                msg += HIY"$p沉著應戰，沒有受到“奪魄”攻擊的影響！\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

void end(object target,int damage)
{
        if (! objectp(target)) return;
        delete_temp("sword", target);
        addn_temp("apply/attack", 0-damage, target);
        addn_temp("apply/defense", 0-damage, target);
        message_vision(RED"$N終于從奪魄的陰影裡恢復了出來。\n"NOR,target);
}

