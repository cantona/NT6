// This program is a part of NITAN MudLIB
// shentong.c 先天功 純陽神通功

// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "純陽神通功" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 240)
                return notify_fail("你的先天功修為不夠，難以施展" + name() + "。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的內力修為不足，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("你沒有激發先天功為拳腳，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("你沒有激發先天功為內功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("你沒有準備使用先天功，難以施展" + name() + "。\n");

        if( query("neili", me)<1000 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIW "$N" HIW "運起純陽神通功，片刻便見白氣逐漸籠罩全身，雙眼精光四射，與平時判若兩人。\n"
              HIW "$N" HIW "接着突然出掌攻向$n，當真是無聲無息，卻迅如閃電。\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        addn("neili", -800, me);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 600,
                               HIR "$n" HIR "來不及反應，即被$N純陽神通功驚人神功擊中。\n" NOR "( $n"
                               RED "受傷過重，已經有如風中殘燭，隨時都可能斷氣"
                               "。" NOR ")\n" NOR);
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        addn("neili", -500, me);
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300,
                                                   HIR "結果$N" HIR "純陽神通功正中$n" HIR "胸"
                                                   "口，純陽神通功登時透胸而入，$n" HIR "接連噴出數"
                                                   "口鮮血。\n" NOR);
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -120, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，但卻很狼狽的躲避開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;
}
