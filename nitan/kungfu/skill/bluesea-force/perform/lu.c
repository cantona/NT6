// lu.c 戮仙決
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("戮仙決只能對戰鬥中的對手使用。\n");
 
        if (me->query_skill("bluesea-force", 1) < 120)
                return notify_fail("你的南海玄功還不夠嫻熟，不能使用戮仙決！\n");

        if( query("neili", me)<200 )
                return notify_fail("你的內力不夠，不能使用戮仙決！\n");
 
       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "嘿然冷笑，拍出一掌，吞吞吐吐，變化莫測，攻向$n"
              HIC "！\n" NOR;
 
        ap = attack_power(me, "force") + me->query_con();
        dp = defense_power(target, "parry") + target->query_con();

        me->start_busy(2);
        addn("neili", -50, me);
        if (ap / 2 + random(ap) < dp)
        {
                msg += HIG "然而$n" HIG "看破了$N" HIG
                       "的掌勢，不慌不忙的躲過了這一擊！\n" NOR;
        } else
        {
                addn("neili", -75, me);
                damage = damage_power(me, "force");
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                           HIR "$n" HIR "不明所以，運功抵擋，只覺得$P的掌力怪"
                                           "異之極，直滲入至奇經八脈，登時受了內傷！\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}