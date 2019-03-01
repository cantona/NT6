// shou.c 九陰神手

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
#define SHOU  "「" HIG "九陰神手" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, ap1, dp1, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHOU "只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("此招只能空手施展！\n");

        if (me->query_skill("jiuyin-shengong", 1) < 260)
                return notify_fail("你的九陰神功還不夠嫻熟，不能使用" SHOU "！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠！\n");

        if (me->query_skill_mapped("hand") != "jiuyin-shengong"
           && me->query_skill_prepared("unarmed") != "jiuyin-shengong")
                return notify_fail("你沒有準備使用九陰神功，無法施展" SHOU "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "“哈”的一聲吐出了一口氣，手式奇特，軟綿綿的奔向$n"
              HIY "的要穴！\n";

        ap = attack_power(me, "hand");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                ap = me->query_skill("jiuyin-shengong");
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(3));

                me->want_kill(target);

                if (dp >= 10000) // 此招對千萬經驗以上的人無效
                { // 但是仍然受到傷害
                        damage = damage_power(me, "hand");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                        HIR "$n" HIR "只覺此招，陰柔無比，詭異莫測，"
                                        "心中一驚，卻猛然間覺得一股陰風透骨而過。\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "這一招完全超出了$n" HIR "的想象，被$N"
                                HIR "結結實實的打中了檀中大穴，渾身真氣登時渙散！\n" NOR;
                        message_combatd(msg, me, target);
                        addn("neili", -200, me);
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