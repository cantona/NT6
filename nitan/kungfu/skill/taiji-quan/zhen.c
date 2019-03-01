// zhen.c 太極拳「震」字訣

#include <ansi.h>
#include <combat.h>

string name() { return "震字訣"; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        string force;

        if(! target) target = offensive_target(me);

        if(! target || ! target->is_character() || ! me->is_fighting())
                return notify_fail("「" + name() + "」只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("你必須空手才能使用「" + name() + "」。\n");

        if((int)me->query_skill("taiji-quan", 1) < 180)
                return notify_fail("你的太極拳不夠嫻熟，不會使用「" + name() + "」。\n");

        if((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的內功不夠高，不能用來反震傷敵。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在內力太弱，震也震不傷敵人。\n");

        msg = HIY "$N" HIY "默運神功，真氣流轉，雙手左右連畫，一個圓圈已將$n"
              HIY "套住，\n太極拳中的「" HIW + name() + HIY "」信手使出，一道"
              HIY "渾厚的內力向$n" HIY "推去！\n" NOR;

        ap = attack_power(me, "cuff") + me->query_skill("force");
        dp = defense_power(target, "parry") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                if( query("neili", me)<query("neili", target) )
                {
                        damage = damage_power(me, "cuff");
                        damage+= query("jiali", me);

                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                                   HIC "\n眼見$P" HIC "就要將$p震倒，突然，$n"
                                                   HIC "運起全身內力，強忍疼痛硬接了$P一招。\n" NOR);
                        if (! target->is_busy())
                                target->start_busy(3);
                        me->start_busy(3);
                        addn("neili", -(query("neili", target)/2), target);
                        addn("neili", -(query("neili", me)/(2+random(2))), me);
                }
                else
                {
                        damage = damage_power(me, "cuff");
                        damage+= query("jiali", me);

                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 300,
                                                   HIC "\n眼見$n" HIC "被$P的內力壓得透不過起來，只聽得$N"
                                                   HIC "“砰”的一聲擊中$n" HIC "，$p全身骨骼便似散了"
                                                   HIC "架一般倒了下去。\n" NOR);
                        me->start_busy(2);
                        if( !target->is_busy() )
                                target->start_busy(3);
                        addn("neili", -(query("neili", me)/(2+random(3))), me);
                }
        }
        else
        {
                msg += HIG "\n可$p竟隨手便把$P匯聚全身功力的招數架開，嚇得$P手足無措！\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target, 0, 1);
        return 1;
}
