#include <ansi.h>
#include <combat.h>

#define KAI "「" WHT "混沌初開" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
        
        if( userp(me) && !query("can_perform/baisheng-quan/kai", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(KAI "只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("只有空手才能施展" KAI "。\n");

        if ((int)me->query_skill("baisheng-quan", 1) < 100)
                return notify_fail("你的百勝神拳不夠嫻熟，難以施展" KAI "。\n");

        if ((int)me->query_skill("force") < 140)
                return notify_fail("你的內功修為不夠，難以施展" KAI "。\n");

        if (me->query_skill_mapped("cuff") != "baisheng-quan") 
                return notify_fail("你沒有激發百勝神拳，難以施展" KAI "。\n");

        if (me->query_skill_prepared("cuff") != "baisheng-quan")
                return notify_fail("你沒有準備百勝神拳，難以施展" KAI "。\n");

        if( query("neili", me)<200 )
                return notify_fail("你現在的真氣不足，難以施展" KAI "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "身子驀的橫移，兩臂向後反鉤，呼的一聲朝$n"
              WHT "攻去，正是「" NOR + HIR "混沌初開" NOR + WHT "」絕"
              "技。\n" NOR;
              
        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");
        
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                damage = damage_power(me, "cuff");
                addn("neili", -100, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "結果$n" HIR "閃避不及，$N" HIR "雙"
                                           "拳正中$p" HIR "頭部兩側，頓時口噴鮮血"
                                           "，幾欲昏厥。\n" NOR);
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