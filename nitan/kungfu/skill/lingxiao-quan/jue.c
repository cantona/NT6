#include <ansi.h>
#include <combat.h>

string name() { return HIW "凌宵總訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" + name() + "。\n");

        if ((int)me->query_skill("lingxiao-quan", 1) < 60)
                return notify_fail("你的凌霄拳法不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "lingxiao-quan")
                return notify_fail("你沒有激發凌霄拳法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "lingxiao-quan")
                return notify_fail("你現在沒有準備使用凌霄拳法，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "只聽$N" HIW "一聲斷喝，雙拳聚力齊發，一式「凌霄總決」攜"
              "著風雷之勢轟向$n" HIW "！\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "cuff");
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 40,
                                           HIR "結果$p" HIR "閃避不及，被$P" HIR
                                           "一拳正中面門，頓時口噴鮮血，幾乎昏厥"
                                           "！\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -30, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}