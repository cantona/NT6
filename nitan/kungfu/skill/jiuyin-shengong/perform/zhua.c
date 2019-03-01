// zhua.c 九陰神抓

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZHUA "「" HIR "九陰神爪" NOR "」"

int perform(object me, object target)
{
        int damage;
        string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUA "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail(ZHUA "只能空手施展！\n");

        if ((int)me->query_skill("jiuyin-shengong", 1) < 280)
                return notify_fail("你的九陰神功還不夠嫻熟，不能使用" ZHUA "。\n");
                                
        if( query("neili", me)<300 )
                return notify_fail("你現在內力太弱，不能使用" ZHUA "。\n");

//        if (me->query_skill_prepared("claw") != "jiuyin-shengong")
        if (me->query_skill_mapped("claw") != "jiuyin-shengong")
                return notify_fail("你沒有準備使用九陰神功，無法施展" ZHUA "。\n");
       
       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "微微一笑，右手成爪，忽的抓向$n"
              HIY "的要穴！\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "claw");
        dp = defense_power(target, "parry");

        me->want_kill(target);
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -180, me);
                damage = 0;

                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "$N" HIR "這一爪來勢好快，正抓中$n"
                               HIR "的檀中大穴，$n" HIR
                               "一聲慘叫，軟綿綿的癱了下去。\n" NOR;
                        damage = -1;
                } else
                {
                        if (! target->is_busy())
                        target->start_busy(1 + random(3));
        
                        damage = damage_power(me, "claw");
                        
                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "要害";
                        pmsg = HIR "$n連忙騰挪躲閃，然而“撲哧”一聲，$N"
                               HIR "五指正插入$n" HIR "的" + limb + "，$n"
                               HIR "一聲慘叫，血濺五步。\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90, pmsg);
                }
        } else 
        {
                me->start_busy(2);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的來勢，接應得法，避開了這一抓。\n"NOR;
        }

        message_combatd(msg, me, target);
        if (damage < 0) target->die(me);

        return 1;
}
