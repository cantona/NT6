// xian.c  雲龍三現

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("雲龍三現只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
                
        if ((int)me->query_skill("yunlong-jian", 1) < 50)
                return notify_fail("你的雲龍劍法不夠嫻熟，不會使用「雲龍三現」。\n");
                                
        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候不夠，不能使用「雲龍三現」。\n");
                        
        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，不能使用「雲龍三現」。\n");
                        
        msg = HIM "$N" HIM "微微一笑，猛吸一口氣，以氣馭劍攻擊虛虛實實的攻向$n"
              HIM "！\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
        
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                addn("neili", -180, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "只見$N" HIR "手中劍光幻作一條金龍，騰空而"
                                           "起倏的罩向$n" HIR "，\n$p" HIR "只覺一股大力"
                                           "舖天蓋地般壓來，登時眼前一花，兩耳轟鳴，哇的"
                                           "噴出一口鮮血！！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "猛地向前一躍，跳出了$P"
                       CYN "的攻擊范圍。\n"NOR;
                addn("neili", -100, me);
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}
