#include <ansi.h>
#include <combat.h>

#define ZHEN "「" WHT "八卦震" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if( userp(me) && !query("can_perform/wai-bagua/zhen", me) )
                return notify_fail("你所使用的外功中沒有這種功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(ZHEN "只能空手施展。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不足，難以施展" ZHEN  "。\n");

        if ((int)me->query_skill("wai-bagua", 1) < 60)
                return notify_fail("你的外八卦不夠嫻熟，難以施展" ZHEN  "。\n");
                                
        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不足，難以施展" ZHEN  "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = WHT "$N" WHT "深吸一口氣，雙掌交錯，一招「八卦震」平平拍出，企"
              "圖以內力震傷$n" WHT "。\n" NOR;
        addn("neili", -50, me);

        if (random(me->query_skill("force")) > target->query_skill("force") / 2)
        {
                me->start_busy(3);
                target->start_busy(random(3));

                damage = (int)me->query_skill("wai-bagua", 1);
                damage = damage / 2 + random(damage / 2);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 30,
                                           HIR "結果$n" HIR "微微一楞，沒有看破招"
                                           "中奧妙，$N" HIR "雙掌正好拍在胸前。\n"
                                           NOR ":內傷@?");
        } else 
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，並沒有上當。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}