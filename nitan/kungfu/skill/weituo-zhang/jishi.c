#include <ansi.h>
#include <combat.h>

#define JISHI "「" HIB "即世即空" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/weituo-zhang/jishi", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JISHI "只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(JISHI "只能空手施展。\n");

        if ((int)me->query_skill("weituo-zhang", 1) < 120)
                return notify_fail("你韋陀掌不夠嫻熟，難以施展" JISHI "。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功修為不夠，難以施展" JISHI "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不夠，難以施展" JISHI "。\n");

        if (me->query_skill_mapped("strike") != "weituo-zhang") 
                return notify_fail("你沒有激發韋陀掌，難以施展" JISHI "。\n");

        if (me->query_skill_prepared("strike") != "weituo-zhang")
                return notify_fail("你沒有準備韋陀掌，難以施展" JISHI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIB "只見$N" HIB "雙掌一錯，揉身而進，連環攻出數掌，一環環"
              "向$n" HIB "劈去。\n" NOR;

        if (random(me->query_skill("strike")) > target->query_skill("dodge") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("strike");
                damage = damage / 2 + random(damage / 2);
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 20,
                                           HIR "$n" HIR "一驚，被$N" HIR "掌勁重重的擊"
                                           "在胸前，登時嘔出一口鮮血！\n" NOR);
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