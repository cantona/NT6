// This program is a part of NITAN MudLIB
// san.c 天女散花

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "天女散花"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("天女散花只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("sanhua-zhang", 1) < 135)
                return notify_fail("你的散花掌法不夠嫻熟，不會使用天女散花。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功修為不夠，難以施展天女散花。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在真氣不夠，無法使用天女散花。\n");

        if (me->query_skill_mapped("strike") != "sanhua-zhang")
                return notify_fail("你沒有激發散花掌，無法使用天女散花！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "$N" HIY "哈哈一笑，雙掌一錯，忽然化作漫天"
              "掌影，猶如千百隻手掌一齊攻向$n" HIY "！\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "結果$p" HIR "沒能避開$P" HIR
                                           "變幻莫測的掌法，蓬蓬接連中了數掌，"
                                           "被打得口噴鮮血，幾乎摔倒！\n" NOR);
                me->start_busy(1 + random(2));
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
