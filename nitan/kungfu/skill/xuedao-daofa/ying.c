// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "無影神刀" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((int)me->query_skill("force") < 160)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 120)
                return notify_fail("你的血刀大法還不到家，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("你沒有激發血刀大法為刀法，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的真氣不夠，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = WHT "$N" WHT "一聲獰笑，將手中的" + weapon->name() +
              WHT "舞動如輪，刀鋒激起層層" HIR "血浪" NOR +
              WHT "緊逼$n" WHT "而去。\n" NOR;

        addn("neili", -80, me);
        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "結果$p" HIR "被$P" HIR "逼得手忙腳"
                       "亂，只能緊守門户，不敢擅動。\n" NOR;
                target->start_busy(ap / 80 + 2);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企圖"
                       "，並不慌張，應對自如。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
