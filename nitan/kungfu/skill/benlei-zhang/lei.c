#include <ansi.h>
#include <combat.h>

#define LEI "「" HIY "雷霆萬鈞" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/benlei-zhang/lei", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(LEI "只能對戰鬥中的對手使用。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(LEI "只能空手施展。\n");

        if ((int)me->query_skill("benlei-zhang", 1) < 120)
                return notify_fail("你的霹靂奔雷掌還不夠嫻熟，難以施展" LEI "。\n");

        if (me->query_skill_mapped("strike") != "benlei-zhang")
                return notify_fail("你沒有激發霹靂奔雷掌，難以施展" LEI "。\n");

        if (me->query_skill_prepared("strike") != "benlei-zhang")
                return notify_fail("你沒有準備霹靂奔雷掌，難以施展" LEI "。\n");

        if( query("neili", me)<400 )
                return notify_fail("你現在真氣不夠，難以施展" LEI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIY "只見$N" HIY "聚力于掌，平平推出，頓時掌風澎湃，掌力"
              "攜著雷霆萬鈞之勢猛貫向$n" HIY "而去！\n" NOR;
        
        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(3);

                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 45,
                                           HIR "結果只聽$n" HIR "一聲悶哼，$N"
                                           HIR "掌勁穿胸而過，“哇”的噴出一大"
                                           "口鮮血。\n" NOR);
                addn("neili", -300, me);
        } else
        {
                me->start_busy(2);
                addn("neili", -200, me);
                msg += CYN "可是$p" CYN "看破了$N" CYN
                       "的企圖，躲開了這招殺著。\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}