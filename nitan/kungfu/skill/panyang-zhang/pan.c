#include <ansi.h>
#include <combat.h>

#define PAN "「" HIR "攀陽邀月" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if( userp(me) && !query("can_perform/panyang-zhang/pan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(PAN "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("panyang-zhang", 1) < 60)
                return notify_fail("你的攀陽掌不夠嫻熟，難以施展" PAN "。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功修為不夠，難以施展" PAN "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不夠，難以施展" PAN "。\n");

        if (me->query_skill_mapped("strike") != "panyang-zhang")
                return notify_fail("你沒有激發攀陽掌，難以施展" PAN "。\n");

        if (me->query_skill_prepared("strike") != "panyang-zhang")
                return notify_fail("你現在沒有準備使用攀陽掌，難以施展" PAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIR "只聽$N" HIR "一聲斷喝，雙掌紛飛，一式「攀陽邀月」接"
              "二連三向$n" HIR "攻去。\n" NOR;
        
        ap = attack_power(me, "strike");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "strike");
                addn("neili", -50, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "結果$p" HIR "閃避不及，被$P" HIR
                                           "接連擊中數掌，頓時口噴鮮血，幾乎昏厥"
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