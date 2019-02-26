// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIC "海淵式" NOR; }

inherit F_SSERVER;

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

        if ((int)me->query_skill("zhemei-shou", 1) < 130)
                return notify_fail("你的逍遙折梅手等級不夠，難以施展" + name() + "。\n");

        if( query("neili", me)<300 )
                return notify_fail("你現在真氣不足，難以施展" + name() + "。\n");

        if (! living(target))
                return notify_fail("對方都已經這樣了，用不着這麼費力吧？\n");

        msg = HIB "$N" HIB "揮手疾舞，施出逍遙折梅手「海淵式」，手法"
              "縹緲，虛虛實實罩向$n" HIB "要害。\n" NOR;

        addn("neili", -50, me);
        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "hand");
                damage+= query("jiali", me);
                addn("neili", -100, me);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "霎時漫天掌影化為一抓，$p" HIR "閃"
                                           "避不及，被$N" HIR "五指插入胸膛，鮮血"
                                           "四處飛濺！\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -50, me);
                msg += HIC "可是$p" HIC "身手敏捷，身形急轉，巧妙的躲過了$P"
                       HIC "的攻擊。\n"NOR;
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}