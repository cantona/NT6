// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "三花聚頂" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("chongyang-shenzhang", 1) < 120)
                return notify_fail("你的重陽神掌不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("strike") != "chongyang-shenzhang")
                return notify_fail("你沒有激發重陽神掌法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("strike") != "chongyang-shenzhang")
                return notify_fail("你沒有準備重陽神掌法，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "$N" HIY "大喝一聲，合身向$n" HIY "撲上，雙掌同時"
              "擊出，正是一招「" HIW "三花聚頂" HIY "」。\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -200, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "結果$p" HIR "被$P" HIR "的氣勢所"
                                           "攝，慌忙後退，卻被$P" HIR "一掌擊個正"
                                           "中，吐血不止！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -60, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}