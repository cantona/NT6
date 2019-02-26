// juemi.c 天地絕滅
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("天地絕滅只能對戰鬥中的對手使用。\n");
 
        if (me->query_skill("never-defeated", 1) < 120)
                return notify_fail("你的不敗神功還不夠嫻熟，不能使用天地絕滅！\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必須手持兵刃才能施展天地絕滅！\n");
        
        if (me->query_skill_mapped("sword") != "never-defeated") 
                return notify_fail("你現在沒有激發不敗神功為劍法，難以施展天地絕滅。\n"); 

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠，不能使用天地絕滅！\n");
 
        if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "隨便走了幾步，忽然一蕩手中的" + weapon->name() +
              HIC "，迅捷無比的掃向$n" HIC "，變化複雜之極，不可思議！\n" NOR;
 
        ap = attack_power(me, "sword") + me->query_int();
        dp = defense_power(target, "dodge") + target->query_dex();

        me->start_busy(2);
        addn("neili", -50, me);
        if (ap / 2 + random(ap) < dp)
        {
                msg += HIG "只見$n" HIG "並不慌張，只是輕輕一閃，就躲過了$N"
                       HIG "這一擊！\n"NOR;
        } else
        {
                addn("neili", -70, me);
                damage = damage_power(me, "sword");
 
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                           HIR "$n" HIR "連忙格擋，可是這一招實在是鬼神莫"
                                           "測，哪裏琢磨得透？登時中了$P" HIR "的重創！\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}