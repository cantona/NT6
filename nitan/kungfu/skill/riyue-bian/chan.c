// This program is a part of NITAN MudLIB
// chan.c

#include <ansi.h>

inherit F_SSERVER;
string name() { return "纏繞訣"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("牽制攻擊只能對戰鬥中的對手使用。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "whip" )
                return notify_fail("你沒有拿着鞭子。\n");

        if( query("neili", me)<80 )
                return notify_fail("你現在真氣不夠，無法施展「纏繞」訣！\n");

        if (me->query_skill_mapped("whip") != "riyue-bian")
                return notify_fail("你沒有激發日月鞭法，無法施展「纏繞」訣！\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIC "$N" HIC "使出日月鞭法「纏繞」訣，連揮數鞭企圖把$n"
              HIC "的全身纏繞起來。\n";

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "結果$p" HIR "被$P" HIR "攻了個措手不及！\n" NOR;
                target->start_busy(ap/80 +2);
                me->start_busy(1);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企圖，小心應對，並沒有上當。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
