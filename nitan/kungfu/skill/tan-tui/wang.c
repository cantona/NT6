#include <ansi.h>
#include <combat.h>

#define WANG "「" HIY "犀牛望月轉回還" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/tan-tui/wang", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(WANG "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(WANG "只能空手施展。\n");

        if (me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，難以施展" WANG "。\n");

        if ((int)me->query_skill("tan-tui", 1) < 120)
                return notify_fail("你的十二路潭腿不夠嫻熟，難以施展" WANG "。\n");

        if (me->query_skill_mapped("unarmed") != "tan-tui")
                return notify_fail("你沒有激發十二路潭腿，難以施展" WANG "。\n");

        if (me->query_skill_prepared("unarmed") != "tan-tui")
                return notify_fail("你沒有準備十二路潭腿，難以施展" WANG "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你的真氣不夠，難以施展" WANG "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "只見$N" HIY "拔地躍起，凌空一個翻滾，陡然間雙腿便如"
              "流星般向$n" HIY "連續踢至。\n" NOR;

        addn("neili", -50, me);
        ap = me->query_skill("unarmed");
        dp = target->query_skill("force");
        if (ap / 2 + random(ap) > dp)
        {
                damage = me->query_skill("unarmed") / 2;
                damage += random(damage / 3);
                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 35,
                                           HIR "卻聽$n" HIR "一聲慘嚎，已被$P" HIR
                                           "單腿正中前胸，頓時心脈受震，噴出一大"
                                           "口鮮血。\n" NOR);
                me->start_busy(3);
        } else
        {
                msg += CYN "可是$p" CYN "奮力招架，終于將$P"
                       CYN "的雙腿架開，沒有受到任何傷害。\n"NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);

        return 1;
}