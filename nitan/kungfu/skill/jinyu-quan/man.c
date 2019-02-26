// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "金玉滿堂" NOR; }

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

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "只能空手施展。\n");

        if ((int)me->query_skill("jinyu-quan", 1) < 80)
                return notify_fail("你的金玉拳法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("cuff") != "jinyu-quan")
                return notify_fail("你沒有激發金玉拳法，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("cuff") != "jinyu-quan")
                return notify_fail("你沒有準備金玉拳法，難以施展" + name() + "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "雙拳紛飛，氣勢如虹，頓時幻出一片拳影，似乎$n"
              HIY"的全身都被拳影所籠罩。\n" NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "cuff");

                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "結果只聽“砰砰砰砰”幾聲悶響，$p"
                                           HIR "前胸被$P" HIR "轟中數拳，登時嘔出"
                                           "一口鮮血！\n" NOR);
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
