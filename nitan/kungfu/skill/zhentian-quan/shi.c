#include <ansi.h>
#include <combat.h>

#define SHI "「" HIY "石破天驚" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/zhentian-quan/shi", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHI "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(SHI "只能空手施展。\n");

        if ((int)me->query_skill("zhentian-quan", 1) < 80)
                return notify_fail("你的震天拳法不夠嫻熟，難以施展" SHI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠，難以施展" SHI "。\n");
 
        if (me->query_skill_mapped("cuff") != "zhentian-quan")
                return notify_fail("你沒有激發震天拳法，難以施展" SHI "。\n");

        if (me->query_skill_prepared("cuff") != "zhentian-quan")
                return notify_fail("你現在沒有準備使用震天拳法，難以施展" SHI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "猛提內勁，聚力于掌一拳揮出，氣勢有如石破天驚，"
              "攜著呼嘯之聲向$n" HIY "直貫而去！\n" NOR;

        if (random(me->query_skill("cuff")) > target->query_skill("dodge") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("cuff");
                damage = damage / 2 + random(damage / 2);
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "結果$p" HIR "閃避不及，被$P" HIR
                                           "這招打了個正中，拳力掌勁頓時透體而入"
                                           "，頓時口噴鮮血，連退數步。\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}