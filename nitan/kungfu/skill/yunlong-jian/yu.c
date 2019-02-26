// yu.c 以氣馭劍
// by Lonely

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
                return notify_fail("以氣馭劍絕技只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
                
        if( (int)me->query_skill("yunlong-jian", 1) < 50 )
                return notify_fail("你的雲龍劍法不夠嫻熟，不會使用「以氣馭劍」。\n");
                                
        if( (int)me->query_skill("yunlong-shengong", 1) < 50 )
                return notify_fail("你的雲龍神功不夠高，不能用來反震傷敵。\n");
                        
        if( query("neili", me)<500 )
                return notify_fail("你現在內力太弱，不能使用「以氣馭劍」。\n");
                
        if( target->is_busy() )
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧ⅵ\n");
        
        msg = HIC "$N微微一笑，猛吸一口氣,欲使出以氣馭劍絕技攻擊$n。\n"NOR;
        
        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                
                addn("neili", 400, me);
                pmsg = HIR"只見$N手中劍光幻作一條金龍,騰空而起,倏的罩向$n,\n$n只覺一股大力鋪天蓋地般壓來,登時眼前一花，兩耳轟鳴,哇的噴出一口鮮血！！\n"NOR;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50, pmsg);
                me->start_busy(2);
        } else 
        {
                msg += CYN"可是$p猛地向前一躍,跳出了$P的攻擊範圍。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
