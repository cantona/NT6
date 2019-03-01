// lei.c 天打雷劈

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("天打雷劈只能在戰鬥中對對手使用。\n");

        if (me->query_skill("never-defeated", 1) < 150)
                return notify_fail("你的不敗神功還不夠嫻熟，不能使用天打雷劈！\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("你必須手持兵刃才能施展天打雷劈！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "大喝一聲，手中的" + weapon->name() +
              HIC "長劈而下，看似簡單，竟然封住了$n"
              HIC "所有的退路！\n" NOR;

        ap = attack_power(me, "sword");
        dp = attack_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                ap = me->query_skill("never-defeated", 1);
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(2));

                me->want_kill(target);
                if (dp >= 10000)
                {
                        damage = damage_power(me, "sword");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                        HIR "$n" HIR "只覺此招，陰柔無比，詭異莫測，"
                                        "心中一驚，卻猛然間覺得一股陰風透骨而過。\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "$n" HIR "平生何曾見過這樣的招數，全然無法化解，"
                                HIR "頓時被擊中數處要害，頹然倒地！\n" NOR;
                        message_combatd(msg, me, target);
                        target->die(me);
                        return 1;
                }
        } else
        {
                msg += HIM "$n" HIM "大吃一驚，連忙胡亂抵擋，居"
                                "然沒有一點傷害，僥幸得脫！\n" NOR;

                me->start_busy(1 + random(3));
        }

        message_combatd(msg, me, target);

        return 1;
}