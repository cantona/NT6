// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIR "鎖魂勢" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if( !objectp(weapon=query_temp("weapon", me)) ||
              query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if ((int)me->query_skill("chanhun-suo",1) < 70)
                return notify_fail("你的纏魂索功力太淺，使不了" + name() + "。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的內功火候不夠，使不了" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧！\n");

        if (me->query_skill_mapped("whip") != "chanhun-suo")
                return notify_fail("你沒有激發纏魂索法，使不了" + name() + "。\n");

        if( query("neili", me)<150 )
                return notify_fail("你內力不足，無法施展" + name() + "。\n");

        if (! living(target))
               return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIR "$N" HIR "一聲陰笑，使出纏魂索鎖魂絕跡，揮舞出滿天鞭影，將$n"
              HIR "全全籠罩！\n\n" NOR;

        ap = attack_power(me, "whip");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIY "結果$n" HIY "被這排山倒海般的攻擊攻了個措手不及，陷如困境，完全無法脱身！\n" NOR;
                target->start_busy(ap/120 + 2);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖，往後一縱，逃開了攻勢。。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);
        return 1;
}