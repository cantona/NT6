#include <ansi.h>
#include <combat.h>

string name() { return HIC "蘭花拂穴" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("lanhua-shou", 1) < 120)
                return notify_fail("你蘭花拂穴手不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("hand") != "lanhua-shou")
                return notify_fail("你沒有激發蘭花拂穴手，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("hand") != "lanhua-shou")
                return notify_fail("你沒有準備蘭花拂穴手，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "反手輕輕伸出三指，婉轉如一朵盛開的蘭花，輕點$n"
              HIC "脅下要穴。\n";

        ap = attack_power(me, "hand");

        dp = defense_power(target, "parry");
        if (ap / 2 + random(ap) > dp)
        {
                msg +=  HIR "$p" HIR "只覺脅下一麻，已被$P"
                        HIR "點個正著，頓時全身酸軟，呆立當場。\n" NOR;
                target->start_busy(ap / 100 + 2);
                addn("neili", -100, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN
                       "的企圖，輕輕一躍，跳了開去。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
