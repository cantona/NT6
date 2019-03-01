#include <ansi.h> 
#include <combat.h> 

#define HONG "「" HIR "紅霞貫日" NOR "」" 

inherit F_SSERVER; 

int perform(object me, object target) 
{
        int skill, ap, dp, damage; 
        string msg; 
                object weapon;

        if( userp(me) && !query("can_perform/yecha-gun/hongxia", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n"); 

        if (! target) 
        { 
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(HONG "只能對戰鬥中的對手使用。\n"); 

        skill = me->query_skill("yecha-gun", 1);

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對，難以施展" HONG "。\n");
                
        if (skill < 120) 
                return notify_fail("你的夜叉棍法等級不夠，難以施展" HONG "。\n"); 

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" HONG "。\n"); 

        if (me->query_skill_mapped("club") != "yecha-gun") 
                return notify_fail("你沒有激發夜叉棍法，難以施展" HONG "。\n"); 

        if (target->is_busy()) 
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n"); 

        if (! living(target)) 
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n"); 

        msg = HIR "$N" HIR "身形曼妙，手中鐵棍" HIR "虛虛實實，舞出無數的棍影" 
              "宛若滿天的紅霞，將$n重重包圍。\n" NOR; 
        
        addn("neili", -50, me);

        ap = me->query_skill("club"); 
        dp = target->query_skill("parry"); 

        if (ap / 2 + random(ap * 4 / 3) > dp) 
        {
                addn("neili", -150, me);
                damage = ap / 8 + random(ap / 8); 
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30, 
                                           HIR "$n" HIR "只覺$N" HIR "棍影重重，" 
                                           "無所不在，自己無處躲閃，頓時身上" 
                                           "連中數棍，被攻了個措手不及。\n" NOR); 

                me->start_busy(1); 
                if (ap / 2 + random(ap) > dp && ! target->is_busy()) 
                        target->start_busy(ap / 30 + 2); 
        } else 
        {
                msg += CYN "$n" CYN "只見$N" CYN "看破了棍法中的虛實，凝神" 
                       "化解開來。\n" NOR; 
                addn("neili", -80, me);
                me->start_busy(3); 
        } 
        message_combatd(msg, me, target);  

        return 1; 
}