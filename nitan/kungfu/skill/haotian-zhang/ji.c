// haoran.c 浩然一擊

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "浩然一擊"; }

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("浩然一擊只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("haotian-zhang", 1) < 60)
                return notify_fail("你的昊天掌不夠嫻熟，不會使用浩然一擊。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，難以施展浩然一擊。\n");

        if( query("neili", me)<150 )
                return notify_fail("你現在真氣不夠，無法使用浩然一擊。\n");

        if (me->query_skill_mapped("strike") != "haotian-zhang")
                return notify_fail("你現在沒有激發昊天掌法，無法使用浩然一擊。\n");

        if( query_temp("weapon", me) )
                return notify_fail("你必須空手才能夠使用浩然一擊。\n");

        msg = HIC "$N" HIC "大喝一聲，合身向$n" HIC "撲上，雙掌"
              "同時擊出，正是一招「浩然一擊」。\n" NOR;

        ap = attack_power(me, "strike");
        if (living(target))
                dp = defense_power(target, "dodge");
        else    dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -110, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "結果$p" HIR "被$P" HIR "的氣勢所"
                                           "攝，慌忙後退，結果被$P" HIR "一掌擊"
                                           "了個正中，吐血不止！！\n" NOR);
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