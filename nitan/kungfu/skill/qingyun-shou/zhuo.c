// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return WHT "捕風捉影" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage, ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("qingyun-shou", 1) < 50)
                return notify_fail("你的青雲手不夠嫻熟，難以施展" + name() + "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("hand") != "qingyun-shou")
                return notify_fail("你沒有激發青雲手，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("hand") != "qingyun-shou")
                return notify_fail("你現在沒有準備使用青雲手，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "劃身錯步，單手拂過，手影虛虛實實，難辨真偽，完"
              "全籠罩$n" WHT "。\n" NOR;

        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "hand");
                addn("neili", -150, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "$p" HIR "一時辨別不清虛實，被$P"
                                           HIR "手影劃過氣門，氣血翻滾，幾乎窒息。\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -100, me);
                msg += CYN "可是$p" CYN "識破了$P"
                       CYN "這一招，斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
