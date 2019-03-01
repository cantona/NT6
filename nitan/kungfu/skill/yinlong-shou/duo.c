// duo.c 奪命

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "奪命" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, ap1, dp1, damage;
        mixed dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能在戰鬥中對對手使用。\n");

        if( query_temp("weapon", me) )
                return notify_fail("此招只能空手施展！\n");

        if (me->query_skill("yinlong-shou", 1) < 260)
                return notify_fail("你的銀龍手還不夠嫻熟，不能使用" + name() + "！\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠！\n");

        if (me->query_skill_mapped("strike") != "yinlong-shou"
           && me->query_skill_prepared("strike") != "yinlong-shou")
                return notify_fail("你沒有準備使用銀龍手，無法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "雙手匯集了全身的內力，頓時全身衣衫鼓脹，雙目放出驚人的殺氣，\n"
              HIY "在$n" HIY "吃驚之際，$N" HIY "的雙手已如流星閃電般揮出，只見一股強大的氣流朝$n" HIY "心臟插去！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                ap = me->query_skill("yinlong-shou");
                dp=query("combat_exp", target)/10000;
                addn("neili", -60, me);
                me->start_busy(1 + random(3));

                me->want_kill(target);

                if (dp >= 10000) // 此招對千萬經驗以上的人無效
                { // 但是仍然受到傷害
                        damage = damage_power(me, "strike");

                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90,
                                        HIR "$n" HIR "只覺此招，來如閃電，無法招架，"
                                        "心中一驚，卻猛然間覺得一股陰風透骨而過。\n" NOR);
                        addn("neili", -140, me);

                        message_combatd(msg, me, target);
                        // target->start_busy(1 + random(2));
                        return 1;
                } else
                {
                        msg += HIR "這一招完全超出了$n" HIR "的想象，被$N"
                                HIR "雙手插入心臟，頓時喪命！\n" NOR;
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