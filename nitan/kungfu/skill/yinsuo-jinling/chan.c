// This program is a part of NITAN MudLIB
// chan.c 纏字訣

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIC "纏字訣" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("牽制攻擊只能對戰鬥中的對手使用。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("yinsuo-jinling", 1) < 80)
                return notify_fail("你銀鎖金鈴的修為不夠，不能使用纏字訣！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        msg = CYN "$N" CYN "使出銀鎖金鈴「纏」字訣，拂鞭連揮企圖把$n"
              CYN "的全身纏住。\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += CYN "結果$p" CYN "被$P" CYN "攻了個措手不及。\n" NOR;
                target->start_busy( me->query_skill("whip", 1) / 100 + 2 );
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，並沒有上當。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        addn("neili", -100, me);
        return 1;
}