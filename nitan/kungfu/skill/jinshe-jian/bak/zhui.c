// This program is a part of NITAN MudLIB
// zhui.c  追命

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg, pmsg;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("「追命」只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
                
        if( (int)me->query_skill("jinshe-jian", 1) < 150 )
                return notify_fail("你的金蛇劍法不夠嫻熟，不會使用。\n");
                                
        if( query("neili", me)<800 )
                return notify_fail("你現在內力太弱，不能使用「追命」。\n");
                        
        msg = HIY "$N微微一笑，劍意若有若無，$n卻感到莫大的壓力。\n"NOR;

        me->want_kill(target);
        if( !target->is_killing(me) ) 
                target->kill_ob(me);
        
        ap=me->query_skill("sword")*3/2+query("level", me)*20+
             me->query_skill("martial-cognize", 1);
        dp=target->query_skill("force")+query("level", target)*20+
             target->query_skill("martial-cognize", 1);

        if (ap / 2 + random(ap) > dp)
        {
                if (! target->is_busy())
                target->start_busy( random(2) + 2);
                
                damage = (int)me->query_skill("jinshe-jian", 1) / 2;
                
                addn("neili", -400, me);
                pmsg = HIR "只見$N劍走了個怪異的弧線，從不可思議的角度向$n殺去,\n$n只覺得背心一陣冰涼，呆呆地看著前胸的劍尖！\n" NOR;
                
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40, pmsg);
                me->start_busy(2);
        } else 
        {
                msg += CYN"可是$p猛地向前一躍,跳出了$P的攻擊范圍。\n"NOR;
                addn("neili", -200, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
