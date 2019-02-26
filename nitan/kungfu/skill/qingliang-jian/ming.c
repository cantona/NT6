#include <ansi.h> 
#include <combat.h> 

#define SHENG "「" HIW "禪心自明" NOR "」" 

inherit F_SSERVER; 

int perform(object me, object target) 
{ 
        object weapon; 
        string msg; 
        int ap, dp; 
        int damage; 

        
        if (! target) target = offensive_target(me); 

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(SHENG "只能在戰鬥中對對手使用。\n"); 

        if( userp(me) && !query("can_perform/qingliang-jian/ming", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");   

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" SHENG "。\n"); 

        if (me->query_skill("force") < 100) 
                return notify_fail("你的內功的修為不夠，難以施展" SHENG "。\n"); 

        if (me->query_skill("qingliang-jian", 1) < 80) 
                return notify_fail("你的清涼劍法修為不夠，難以施展" SHENG "。\n"); 

        if (me->query_skill_mapped("sword") != "qingliang-jian") 
                return notify_fail("你沒有激發清涼劍法，難以施展" SHENG "。\n"); 

        if( query("neili", me)<80 )
                return notify_fail("你現在真氣不夠，難以施展" SHENG "。\n"); 

        if (! living(target)) 
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n"); 

        msg = HIW "$N" HIW "一抖手中" + weapon->name() + HIW "閃出無數個劍花，同時向$n" HIW "刺去。\n" NOR; 
        ap = me->query_skill("sword"); 
        dp = target->query_skill("parry"); 

        if (ap * 2 / 3 + random(ap) > dp) 
        {
                damage = ap / 3 + random(ap / 2); 
                addn("neili", -40, me);
                me->start_busy(2); 
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 20, 
                                           HIR "$n" HIR "看的頭昏眼花，不知虛實，登時$n" 
                                           HIR "身上幾處受傷！\n" NOR); 
        } else 
        {
                addn("neili", -20, me);
                me->start_busy(3); 
                msg += CYN "可是$p" CYN "看破其中虛實，輕輕架開了$P" 
                       CYN "的劍招。\n"NOR; 
        }

        message_combatd(msg, me, target); 

        return 1; 
}
