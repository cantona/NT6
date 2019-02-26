// wanli.c 晴空萬里

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object  weapon;
        int     damage;
        string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("晴空萬里只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("never-defeated", 1) < 120)
                return notify_fail("你的不敗神功還不夠嫻熟，不能使用晴空萬里。\n");
                                
        if( query("neili", me)<200 )
                return notify_fail("你現在內力太弱，不能使用晴空萬里。\n");
                        
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必須手持兵刃才能施展晴空萬里！\n");
                
        if (me->query_skill_mapped("sword") != "never-defeated") 
                return notify_fail("你現在沒有激發不敗神功為劍法，難以施展晴空萬里。\n"); 
                
        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "懷抱" + weapon->name() + HIC "，一"
              "圈圈的划向$n" HIC "，將$p" HIC "卷在當中！\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -180, me);

                damage = damage_power(me, "sword");

                if( arrayp(limbs=query("limbs", target)) )
                        limb = limbs[random(sizeof(limbs))];
                else
                        limb = "要害";
                pmsg = HIR "$n連忙騰挪躲閃，然而“撲哧”一聲，" + weapon->name() +
                       HIR "正好擊中$p" HIR "的" + limb + "，$p"
                       HIR "一聲慘叫，連退數步。\n" NOR;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90, pmsg);
        } else 
        {
                me->start_busy(2);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的變化，見招拆招，沒有受到任何傷害。\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
