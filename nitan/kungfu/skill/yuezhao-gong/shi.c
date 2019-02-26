#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "弒元訣" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "只能對戰鬥中的對手使用。\n");

        if( objectp(weapon=query_temp("weapon", me)) )
                return notify_fail(name() + "只能空手施展。\n");

        if (me->query_skill("force") < 200)
                return notify_fail("你的內功火候不夠，難以施展" + name() + "。\n");

        if ((int)me->query_skill("yuezhao-gong", 1) < 130)
                return notify_fail("你越爪功等級不夠，難以施展" + name() + "。\n");

        if (me->query_skill_mapped("claw") != "yuezhao-gong")
                return notify_fail("你沒有激發越爪功，難以施展" + name() + "。\n");

        if (me->query_skill_prepared("claw") != "yuezhao-gong")
                return notify_fail("你沒有準備越爪功，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在的真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = WHT "$N" WHT "施出越爪功「" HIR "弒元訣" NOR + WHT "」絕技，右"
              "手一橫，直直抓向$n" WHT "破綻所在。\n" NOR;

        addn("neili", -100, me);
        ap = attack_power(me, "claw");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "claw");
                addn("neili", -50, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "只聽$n" HIR "一聲慘嚎，竟被$N" HIR
                                           "的五指抓破氣門，鮮血登時四處飛濺！\n" NOR);
                me->start_busy(2);
        } else
        {
                msg += HIC "可是$p" HIC "身手敏捷，身形急轉，巧妙的躲過了$P"
                       HIC "的攻擊。\n"NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}