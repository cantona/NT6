#include <ansi.h>
#include <combat.h>

#define JUAN "「" HIY "風捲霹靂上九天" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/hua-quan/juan", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JUAN "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(JUAN "只能空手施展。\n");

        if ((int)me->query_skill("hua-quan", 1) < 120)
                return notify_fail("你的西嶽華拳不夠嫻熟，難以施展" JUAN "。\n");

        if ((int)me->query_skill("force") < 180)
                return notify_fail("你的內功修為不夠，難以施展" JUAN "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在真氣不夠，難以施展" JUAN "。\n");

        if (me->query_skill_mapped("cuff") != "hua-quan") 
                return notify_fail("你沒有激發西嶽華拳，難以施展" JUAN "。\n");

        if (me->query_skill_prepared("cuff") != "hua-quan")
                return notify_fail("你現在沒有準備使用西嶽華拳，難以施展" JUAN "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIY "只見$N" HIY "身形疾轉，雙拳聚力齊發，一式「風捲霹靂上九天」攜"
              "着隱隱風雷之勢貫向$n" HIY "！\n" NOR;

        if (random(me->query_skill("cuff")) > target->query_skill("dodge") / 2)
        {
                me->start_busy(2);
                damage = me->query_skill("cuff");
                damage = damage / 2 + random(damage);
                addn("neili", -250, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "結果$n" HIR "閃避不及，被$P" HIR
                                           "雙拳貫中，悽然一聲慘嚎，口噴鮮血，身"
                                           "子向後飛出丈許。\n" NOR);
        } else
        {
                me->start_busy(3);
                addn("neili", -80, me);
                msg += CYN "$p" CYN "見$P" CYN "拳勢洶湧，不敢硬"
                       "作抵擋，當即斜斜一躍避開。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}