#include <ansi.h>
#include <combat.h>

string name() { return HIG "碧浪滔天" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("canglang-zhi", 1) < 80)
                return notify_fail("你滄浪指法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("finger") != "canglang-zhi")
                return notify_fail("你沒有激發滄浪指法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("finger") != "canglang-zhi")
                return notify_fail("你沒有準備滄浪指法，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIG "$N" HIG "陡然施出一勢「碧浪滔天」，十指紛翻，指氣嗤然作"
              "響，全全籠罩$n" HIG "。\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "finger");
                addn("neili", -80, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "結果$n" HIR "躲閃不及，被$N" HIR
                                           "一指命中，全身氣血翻騰不已。\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -50, me);
                msg += CYN "可是$n" CYN "識破了$N"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}