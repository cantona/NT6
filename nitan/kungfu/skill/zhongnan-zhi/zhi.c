#include <ansi.h>
#include <combat.h>

string name() { return HIG "劍指南山" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("zhongnan-zhi", 1) < 60)
                return notify_fail("你終南指法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "zhongnan-zhi")
                return notify_fail("你沒有激發終南指法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "zhongnan-zhi")
                return notify_fail("你沒有準備終南指法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<60 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIG "$N" HIG "斜斜一指刺出，指尖晃動不已，遙遙點向$n"
              HIG "要穴所在。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "finger");
                addn("neili", -60, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "結果$p" HIR "招架失誤，被$P" HIR
                                           "這一指點了個正著，內息登時一滯，氣血倒流。\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -20, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}