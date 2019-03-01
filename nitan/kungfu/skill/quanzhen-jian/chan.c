// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "纏字訣" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level;
        string msg;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對，難以施展" + name() + "。\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顧不暇，放膽攻擊吧。\n");

        if ((level = me->query_skill("quanzhen-jian", 1)) < 80)
                return notify_fail("你全真劍法不夠嫻熟，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("sword") != "quanzhen-jian")
                return notify_fail("你沒有激發全真劍法，難以施展" + name() + "。\n");

        if( query("neili", me)<100 )
                return notify_fail("你現在的真氣不夠，難以施展" + name() + "。\n");

       if (! living(target))
              return notify_fail("對方都已經這樣了，用不著這麼費力吧？\n");

        msg = HIC "$N" HIC "使出全真劍法「纏」字訣，" + weapon->name() +
              HIC "帶出陣陣風聲，從四面八方盤繞向$n" HIC "。\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(1);
                msg += HIR "$p" HIR "只覺得$P" HIR
                       "劍上壓力一層強過一層，只能使盡渾身解數運功抵擋。\n" NOR;
                target->start_busy(ap / 90 + 2);
        } else
        {
                msg += CYN "$p" CYN "見$P" CYN "招法嚴謹，當下不敢小覷"
                       "，巧妙拆解$P" CYN "的來招，不露半點破綻。\n" NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}
