// zhi.c 幽冥神指

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("幽冥神指只能在戰鬥中對對手使用。\n");

        if (me->query_skill("kuihua-mogong", 1) < 150)
                return notify_fail("你的葵花魔功還不夠嫻熟，不能使用幽冥神指！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠！\n");

        if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "$N" HIR "進步欺前，隨即一指無聲無息的向$n" HIR "的要害刺出！\n";

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->want_kill(target);
                ap = me->query_skill("kuihua-mogong", 1);
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(2));

                if (dp >= 10000)
                {
                        damage = damage_power(me, "finger");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                        HIR "$n" HIR "只覺此招，陰柔無比，詭異莫測，"
                                        "心中一驚，卻猛然間覺得一股陰風透骨而過。\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "這一招速度之快完全超出了$n" HIR "的想象，被$N"
                                HIR "這一指正好刺中了丹田要害，渾身真氣登時渙散！\n" NOR;
                        message_combatd(msg, me, target);
                        target->die(me);
                        return 1;
                }
        } else
        {
                msg += HIM "$n" HIM "大吃一驚，連忙退後，居然"
                                "僥幸躲開著這一招！\n" NOR;
                me->start_busy(1 + random(2));
        }

        message_combatd(msg, me, target);

        return 1;
}