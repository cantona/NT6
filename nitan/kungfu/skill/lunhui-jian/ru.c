#include <ansi.h> 
#include <combat.h> 

#define RU "「" HIR "我入地獄" NOR "」" 

inherit F_SSERVER; 

string final(object me, object target, int damage); 

int perform(object me, object target) 
{
        object weapon; 
        string msg; 
        int ap, dp; 
        int damage; 

        if( userp(me) && !query("can_perform/lunhui-jian/ru", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me); 

        if (! target || ! me->is_fighting(target)) 
                return notify_fail(RU "只能對戰鬥中的對手使用。\n"); 

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" RU "。\n"); 

        if ((int)me->query_skill("lunhui-jian", 1) < 200) 
                return notify_fail("你的釋迦輪回劍法不夠嫻熟，難以施展" RU "。\n"); 

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，難以施展" RU "。\n"); 

        if ((int)me->query_skill("buddhism", 1) < 200) 
                return notify_fail("你現在對佛學領悟不夠，難以施展" RU "。\n"); 

        if (me->query_skill_mapped("sword") != "lunhui-jian")  
                return notify_fail("你沒有激發釋迦輪回劍，難以施展" RU "。\n"); 

        if (! living(target)) 
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n"); 

        msg = HIC "$N" HIC "氣貫手中長劍，一劍去勢沉穩，緩緩的掃向$n" 
              "，看似變化平平。\n" NOR; 

        addn("neili", -80, me);
        ap = me->query_skill("sword"); 
        dp = target->query_skill("parry"); 
        if (target->is_bad()) ap += ap / 10; 

        me->start_busy(2); 
        if (ap / 2 + random(ap) > dp) 
        {
                damage = ap + random(ap / 3); 
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 75, 
                                           (: final, me, target, damage :)); 
        } else 
        {
                msg += HIC "可是$n" HIC "見識廣博" HIC "，以料到$P劍法的變化" 
                       "，全神應對。\n" NOR; 
        } 
        message_combatd(msg, me, target); 

        return 1; 
}

string final(object me, object target, int damage) 
{
        target->receive_damage("jing", damage / 4, me); 
        target->receive_wound("jing", damage / 8, me); 
        return  HIC "$n" HIC "見劍勢平平，絲毫未把這招放在眼裡，忽然$N" 
                HIC "劍勢一變，手中長\n劍竟盪起層層漣漪，一波一波的逼向$n！\n" NOR + 
                HIR "$n" HIR "對這變化毫無防范，頓時被$P" HIR "這一劍掃中" 
                "，一股血柱自劍芒中激射而出！\n" NOR; 
}
