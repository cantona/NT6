// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "五陰焚滅" NOR; }

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

        if( query("neili", me)<600 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIW "$N" HIW "體內先天真氣急速運轉，單掌一抖，掌心頓時升起一個氣"
              "團，朝$n" HIW "猛拍而去。\n" NOR;

        ap = attack_power(me, "unarmed") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (ap / 2 + random(ap) > dp)
        {
                damage = 0;
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        me->start_busy(2);
                        msg += HIR "$n" HIR "正直詫異間，$N" HIR "一掌已正中$p"
                               HIR "腦門，先天真氣登時貫腦而入。\n" NOR "( $n"
                               RED "受傷過重，已經有如風中殘燭，隨時都可能斷氣"
                               "。" NOR ")\n";
                        damage = -1;
                } else
                {
                        me->start_busy(2);
                        damage = damage_power(me, "unarmed");
                        damage+= query("jiali", me);
                        addn("neili", -500, me);
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90,
                                                   HIR "結果$N" HIR "這掌正中$n" HIR "胸"
                                                   "口，先天真氣登時透體而入，接連噴出數"
                                                   "口鮮血。\n" NOR);
                }
        } else
        {
                me->start_busy(3);
                addn("neili", -120, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍躲避開來。\n" NOR;
        }
        message_combatd(msg, me, target);

        if (damage < 0)
                target->unconcious(me);

        return 1;
}