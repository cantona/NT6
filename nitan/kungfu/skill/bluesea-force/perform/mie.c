// mie.c 五陰焚滅

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
                return notify_fail("五陰焚滅只能在戰鬥中對對手使用。\n");

        if (me->query_skill("bluesea-force", 1) < 150)
                return notify_fail("你的南海玄功還不夠嫻熟，不能使用五陰焚滅！\n");

        if (me->query_skill_mapped("strike") != "bluesea-force")
                return notify_fail("你沒有激發掌法為南海玄功，無法施展五陰焚滅！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "暴喝一聲，變掌為爪，迅捷無比的襲向$n！\n";

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap * 2 / 3 + random(ap) > dp)
        {
                ap = me->query_skill("bluesea-force");
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(2));

                me->want_kill(target);
                // if (dp >= 10000)
                if( query("max_neili", me)<query("max_neili", target)*2 )
                {
                        damage = damage_power(me, "strike");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                        HIR "$n" HIR "只覺此招，陰柔無比，詭異莫測，"
                                        "心中一驚，卻猛然間覺得一股陰風透骨而過。\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "這一招完全超出了$n" HIR "的想象，被$N"
                                HIR "結結實實的抓中了氣海穴，渾身真氣登時渙散！\n" NOR;
                        message_combatd(msg, me, target);
                        target->receive_damage("qi", 100, me);
                        target->die(me);
                        return 1;
                }
        } else
        {
                msg += HIM "$n" HIM "大吃一驚，連忙胡亂抵擋，居"
                                "然沒有一點傷害，僥倖得脱！\n" NOR;

                me->start_busy(1 + random(3));
        }

        message_combatd(msg, me, target);

        return 1;
}