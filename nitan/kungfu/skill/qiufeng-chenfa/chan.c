// chan.c 秋風塵法 纏字訣

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("牽制攻擊只能對戰鬥中的對手使用。\n");

        if( query("neili", me)<200 )
                return notify_fail("你的真氣不夠！\n");

        if ((int)me->query_skill("qiufeng-chenfa", 1) < 80)
                return notify_fail("你秋風塵法的修為不夠，不能使用纏字訣！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        msg = CYN "$N" CYN "使出秋風塵法「纏」字訣，拂塵連揮企圖把$n"
              CYN "的全身纏住。\n" NOR;

        me->start_busy(random(1));
        if( random(query("combat_exp", me)/100)>query("combat_exp", target)/200 )
        {
                msg += CYN "結果$p" CYN "被$P" CYN "攻了個措手不及。\n" NOR;
                target->start_busy( (int)me->query_skill("whip") / 28 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，並沒有上當。\n" NOR;
                me->start_busy(4);
        }
        message_combatd(msg, me, target);
        addn("neili", -100, me);
        return 1;
}